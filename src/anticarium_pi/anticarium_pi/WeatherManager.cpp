#include <anticarium_pi/WeatherManager.h>
#include <cmath>
#include <config/ApplicationSettings.h>
#include <spdlog/spdlog.h>

WeatherManager::WeatherManager(QObject* parent) : QObject(parent) {
    weatherEmulator = new WeatherEmulator(this);
    sampleTimer     = new QTimer(this);
    i2cFetchTimer   = new QTimer(this);

    i2cOutput = new I2COutput(outputParameters, this);
    i2cInput  = new I2CInput(inputParameters, this);

    connect(i2cFetchTimer, &QTimer::timeout, i2cInput, &I2CInput::fetchData);
    connect(sampleTimer, &QTimer::timeout, this, &WeatherManager::sample);

    const auto settings = ApplicationSettings::instance();
    i2cFetchTimer->setInterval(settings->getI2CFetchTimeout());
    sampleTimer->setInterval(settings->getPIDSampleTimeout());
}

void WeatherManager::run() {
    const bool outputConnected = i2cOutput->connectI2c();
    const bool inputConnected  = i2cInput->connectI2c();

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

const shared_types::SensorData& WeatherManager::getSensorData() const {
    return i2cInput->getSensorData();
}

void WeatherManager::setControl(const shared_types::Control& control) {
    SPDLOG_INFO(QString("Set target moisture: %1").arg(control.getRegimeValue().getMoisture()).toStdString());
    SPDLOG_INFO(QString("Set target temperature: %1").arg(static_cast<double>(control.getRegimeValue().getTemperature())).toStdString());

    weatherEmulator->setTargetMoisture(control.getRegimeValue().getMoisture());
    weatherEmulator->setTargetTemperature(control.getRegimeValue().getTemperature());

    send(I2COutput::FAN_PWM, control.getWindPercentage());
    send(I2COutput::FAN_IO, control.getWindPercentage());

    send(I2COutput::LED, control.getLightPercentage());
}

void WeatherManager::sample() const {
    const auto& sensorData = getSensorData();

    const bool water = weatherEmulator->calculateMoistureToggle(sensorData.getMoisture());
    SPDLOG_INFO(QString("Current moisture: %1").arg(sensorData.getMoisture()).toStdString());
    send(I2COutput::WATER, water);

    const float temperature = sensorData.getTemperature();
    // Sometimes invalid temperature gets read
    if (!std::isnan(temperature)) {
        const bool heat = weatherEmulator->calculateHeatToggle(sensorData.getTemperature());
        SPDLOG_INFO(QString("Current temperature: %1").arg(static_cast<double>(temperature)).toStdString());
        send(I2COutput::HEAT, heat);
    }
}

void WeatherManager::send(I2COutput::OutputType outputType, int value) const {
    i2cOutput->send(outputType, static_cast<unsigned char>(value));
}

WeatherManager::~WeatherManager() {
}
