#include <anticarium_pi/WeatherManager.h>
#include <anticarium_pi/config/ApplicationSettings.h>
#include <spdlog/spdlog.h>

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

    ApplicationSettings* settings = ApplicationSettings::instance();
    i2cFetchTimer->setInterval(settings->getI2CFetchTimeout());
    sampleTimer->setInterval(settings->getPIDSampleTimeout());
}

void WeatherManager::run() {
    bool outputConnected = i2cOutput->connectI2c();
    bool inputConnected  = i2cInput->connectI2c();

    if (outputConnected) {
        SPDLOG_INFO("Connected to output i2c");
    } else {
        SPDLOG_ERROR("Could not connect to output i2c");
    }

    if (inputConnected) {
        SPDLOG_INFO("Connected to input i2c");
    } else {
        SPDLOG_ERROR("Could not connect to input i2c");
    }

    i2cFetchTimer->start();
    sampleTimer->start();
}

shared_types::SensorData WeatherManager::getSensorData() const {
    return i2cInput->getSensorData();
}

void WeatherManager::setControl(const shared_types::Control& control) {
    SPDLOG_INFO(QString("Set target moisture: %1").arg(control.getRegimeValue().getMoisture()).toStdString());
    SPDLOG_INFO(QString("Set target temperature: %1").arg(control.getRegimeValue().getTemperature()).toStdString());

    weatherEmulator->setTargetMoisture(control.getRegimeValue().getMoisture());
    weatherEmulator->setTargetTemperature(control.getRegimeValue().getTemperature());

    i2cOutput->send(I2COutput::OutputType::LED, static_cast<unsigned char>(control.getLightPercentage()));
    i2cOutput->send(I2COutput::OutputType::FAN, static_cast<unsigned char>(control.getWindPercentage()));
}

void WeatherManager::sample() {
    shared_types::SensorData sensorData = i2cInput->getSensorData();

    bool heat  = weatherEmulator->calculateHeatToggle(sensorData.getTemperature());
    bool water = weatherEmulator->calculateMoistureToggle(sensorData.getMoisture());

    SPDLOG_INFO(QString("Current temperature: %1").arg(sensorData.getTemperature()).toStdString());
    SPDLOG_INFO(QString("Current moisture: %1").arg(sensorData.getMoisture()).toStdString());

    i2cOutput->send(I2COutput::OutputType::HEAT, heat);
    i2cOutput->send(I2COutput::OutputType::WATER, water);
}

WeatherManager::~WeatherManager() {
}
