#include <anticarium_pi/config/ApplicationSettings.h>

ApplicationSettings* ApplicationSettings::applicationSettings = nullptr;

ApplicationSettings::ApplicationSettings(const QString& directoryPath, QObject* parent) : QObject(parent) {
    settings                = new QSettings(directoryPath, QSettings::IniFormat, this);
    anticariumUrl           = settings->value("Anticarium_Server_URL", "").toString();
    sensorDataSendTimeout   = settings->value("Sensor_Data_send_timeout", 5000).toInt();
    controlDataFetchTimeout = settings->value("Control_Data_fetch_timeout", 5000).toInt();
    pidSampleTimeout        = settings->value("PID_sample_timeout", 3000).toInt();
    i2cFetchTimeout         = settings->value("I2C_fetch_timeout", 1000).toInt();
}

ApplicationSettings* ApplicationSettings::instance(const QString& directoryPath, QObject* parent) {
    if (!applicationSettings) {
        applicationSettings = new ApplicationSettings(directoryPath, parent);
    }
    return applicationSettings;
}

ApplicationSettings* ApplicationSettings::instance() {
    return applicationSettings;
}

ApplicationSettings::~ApplicationSettings() {
    applicationSettings = nullptr;
}

QString ApplicationSettings::getAnticariumUrl() const {
    return anticariumUrl;
}

int ApplicationSettings::getSensorDataSendTimeout() const {
    return sensorDataSendTimeout;
}

int ApplicationSettings::getControlDataFetchTimeout() const {
    return controlDataFetchTimeout;
}

int ApplicationSettings::getPIDSampleTimeout() const {
    return pidSampleTimeout;
}

int ApplicationSettings::getI2CFetchTimeout() const {
    return i2cFetchTimeout;
}
