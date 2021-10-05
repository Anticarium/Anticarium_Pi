#include <anticarium_pi/WeatherManager.h>

WeatherManager::WeatherManager(const shared_types::Control& control, QObject* parent) {
    weatherEmulator = new WeatherEmulator(this);
    sampleTimer     = new QTimer(this);
    i2cFetchTimer   = new QTimer(this);

    I2CWorkerParameters outputParameters;
    outputParameters.address    = 0;
    outputParameters.bufferSize = 2;
    I2CWorkerParameters inputParameters;
    inputParameters.address    = 1;
    inputParameters.bufferSize = 3;

    i2cWorker = new I2CWorker(outputParameters, inputParameters, this);

    connect(i2cFetchTimer, &QTimer::timeout, i2cWorker, &I2CWorker::fetchData);
    connect(sampleTimer, &QTimer::timeout, this, &WeatherManager::sample);
    i2cFetchTimer->setInterval(I2C_FETCH_TIMEOUT);
    sampleTimer->setInterval(SAMPLE_TIMEOUT);
}

void WeatherManager::run() {
    i2cWorker->connectI2c();

    // sample for first time before timer timeout
    i2cWorker->fetchData();
    i2cFetchTimer->start();
    sample();
    sampleTimer->start();
}

shared_types::SensorData WeatherManager::getSensorData() const {
    return i2cWorker->getSensorData();
}

void WeatherManager::setControl(const shared_types::Control& control) {
    weatherEmulator->setTargetTemperature(control.getTemperature());
    weatherEmulator->setTargetMoisture(control.getMoisturePercentage());

    i2cWorker->send(I2CWorker::OutputType::LED, static_cast<unsigned char>(control.getLightPercentage()));
    i2cWorker->send(I2CWorker::OutputType::FAN, static_cast<unsigned char>(control.getWindPercentage()));
}

void WeatherManager::sample() {
    shared_types::SensorData sensorData = i2cWorker->getSensorData();

    bool heat  = weatherEmulator->calculateHeatToggle(sensorData.getTemperature());
    bool water = weatherEmulator->calculateMoistureToggle(sensorData.getMoisture());

    i2cWorker->send(I2CWorker::OutputType::HEAT, heat);
    i2cWorker->send(I2CWorker::OutputType::WATER, water);
}

WeatherManager::~WeatherManager() {
}
