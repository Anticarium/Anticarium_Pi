#include <anticarium_pi/WeatherManager.h>

WeatherManager::WeatherManager(QObject* parent) : QObject(parent) {
    weatherEmulator = new WeatherEmulator(this);
    sampleTimer     = new QTimer(this);
    i2cFetchTimer   = new QTimer(this);

    I2CSlaveParameters outputParameters;
    outputParameters.address    = 0;
    outputParameters.bufferSize = 2;
    I2CSlaveParameters inputParameters;
    inputParameters.address    = 1;
    inputParameters.bufferSize = 3;

    i2cOutput = new I2COutput(outputParameters, this);
    i2cInput  = new I2CInput(inputParameters, this);

    connect(i2cFetchTimer, &QTimer::timeout, i2cInput, &I2CInput::fetchData);
    connect(sampleTimer, &QTimer::timeout, this, &WeatherManager::sample);
    i2cFetchTimer->setInterval(I2C_FETCH_TIMEOUT);
    sampleTimer->setInterval(SAMPLE_TIMEOUT);
}

void WeatherManager::run(const shared_types::Control& initialControl) {
    i2cOutput->connectI2c();
    i2cInput->connectI2c();

    setControl(initialControl);

    i2cFetchTimer->start();
    sampleTimer->start();
}

shared_types::SensorData WeatherManager::getSensorData() const {
    return i2cInput->getSensorData();
}

void WeatherManager::setControl(const shared_types::Control& control) {
    weatherEmulator->setTargetTemperature(control.getTemperature());
    weatherEmulator->setTargetMoisture(control.getMoisturePercentage());

    i2cOutput->send(I2COutput::OutputType::LED, static_cast<unsigned char>(control.getLightPercentage()));
    i2cOutput->send(I2COutput::OutputType::FAN, static_cast<unsigned char>(control.getWindPercentage()));
}

void WeatherManager::sample() {
    shared_types::SensorData sensorData = i2cInput->getSensorData();

    bool heat  = weatherEmulator->calculateHeatToggle(sensorData.getTemperature());
    bool water = weatherEmulator->calculateMoistureToggle(sensorData.getMoisture());

    i2cOutput->send(I2COutput::OutputType::HEAT, heat);
    i2cOutput->send(I2COutput::OutputType::WATER, water);
}

WeatherManager::~WeatherManager() {
}
