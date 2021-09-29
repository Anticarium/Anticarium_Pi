#include <anticarium_pi/WeatherManager.h>

WeatherManager::WeatherManager(const shared_types::Control& control, QObject* parent) {
    sampleTimer = new QTimer(this);
    connect(sampleTimer, &QTimer::timeout, this, &WeatherManager::sample);
    sampleTimer->setInterval(SAMPLE_TIMEOUT);
    weatherEmulator = new WeatherEmulator(this);
}

void WeatherManager::run() {
    // sample for first time before timer
    sample();
    sampleTimer->start();
}

shared_types::SensorData WeatherManager::getSensorData() const {
}

void WeatherManager::setControl(const shared_types::Control& control) {
    weatherEmulator->setTargetTemperature(control.getTemperature());
    weatherEmulator->setTargetMoisture(control.getHumidityPercentage());
}

void WeatherManager::sample() {
    //    weatherEmulator->calculateHeatToggle();
    //    weatherEmulator->calculateMoistureToggle();
}

WeatherManager::~WeatherManager() {
}
