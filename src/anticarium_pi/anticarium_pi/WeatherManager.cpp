#include <anticarium_pi/WeatherManager.h>
#include <anticarium_pi/helper/AnticariumFunctions.hpp>
#include <config/ApplicationSettings.h>
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
    inputParameters.bufferSize = 5;

    i2cOutput = new I2COutput(outputParameters, this);
    i2cInput  = new I2CInput(inputParameters, this);

    connect(i2cFetchTimer, &QTimer::timeout, i2cInput, &I2CInput::fetchData);
    connect(sampleTimer, &QTimer::timeout, this, &WeatherManager::sample);

    auto settings = ApplicationSettings::instance();
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

    i2cOutput->send(I2COutput::LED, static_cast<unsigned char>(control.getLightPercentage()));

    int windPercentage = control.getWindPercentage();
    send(I2COutput::FAN_PWM, windPercentage);
    send(I2COutput::FAN_IO, windPercentage);
}

void WeatherManager::sample() {
    shared_types::SensorData sensorData = i2cInput->getSensorData();

    bool heat  = weatherEmulator->calculateHeatToggle(sensorData.getTemperature());
    bool water = weatherEmulator->calculateMoistureToggle(sensorData.getMoisture());

    SPDLOG_INFO(QString("Current temperature: %1").arg(sensorData.getTemperature()).toStdString());
    SPDLOG_INFO(QString("Current moisture: %1").arg(sensorData.getMoisture()).toStdString());

    send(I2COutput::HEAT, heat);
    send(I2COutput::WATER, water);
}

void WeatherManager::send(I2COutput::OutputType outputType, int value) {
    switch (outputType) {
        case I2COutput::FAN_PWM: {
            // For fan to stop rotating we need to send pwm of 0, which will be
            // inverted on IC side to max pwm and for some reason stop the fan with disabled
            // power
            if (value) {
                value = map<int>(value, 0, 100, 255, 0);
            }
        } break;
        case I2COutput::LED: {
            value = map<int>(value, 0, 100, 0, 255);
        } break;
        case I2COutput::HEAT: {
            value = !value;
        } break;
        default: {
        } break;
    }

    i2cOutput->send(outputType, static_cast<unsigned char>(value));
}

WeatherManager::~WeatherManager() {
}
