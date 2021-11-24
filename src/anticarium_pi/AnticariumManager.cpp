#include <anticarium_pi/AnticariumManager.h>
#include <anticarium_pi/config/ApplicationSettings.h>

AnticariumManager::AnticariumManager(QObject* parent) : QObject(parent) {
    weatherManager      = new WeatherManager(this);
    fetchControlTimer   = new QTimer(this);
    sendSensorDataTimer = new QTimer(this);

    ApplicationSettings* settings = ApplicationSettings::instance();
    fetchControlTimer->setInterval(settings->getControlDataFetchTimeout());
    sendSensorDataTimer->setInterval(settings->getSensorDataSendTimeout());

    JTTP* jttp = JTTP::instance();

    connect(this, &AnticariumManager::requestDataEvent, jttp, &JTTP::onRequestData);
    connect(this, &AnticariumManager::sendDataEvent, jttp, &JTTP::onSendData);
    connect(jttp, &JTTP::dataReceivedEvent, this, &AnticariumManager::applyData);
    connect(fetchControlTimer, &QTimer::timeout, this, &AnticariumManager::onRequestControl);
    connect(sendSensorDataTimer, &QTimer::timeout, this, &AnticariumManager::onSendSensorData);
}

void AnticariumManager::run() {
    onRequestControl(); // Request Control for the first time before timer
    fetchControlTimer->start();
    sendSensorDataTimer->start();
    weatherManager->run();
}

void AnticariumManager::applyData(const shared_types::Control& control) {
    weatherManager->setControl(control);
}

void AnticariumManager::onRequestControl() {
    emit requestDataEvent(JTTP::REQUEST_DATA::CONTROL_DATA);
}

void AnticariumManager::onSendSensorData() {
    shared_types::SensorData sensorData;
    sensorData = weatherManager->getSensorData();
    emit sendDataEvent(sensorData);
}

AnticariumManager::~AnticariumManager() {
}
