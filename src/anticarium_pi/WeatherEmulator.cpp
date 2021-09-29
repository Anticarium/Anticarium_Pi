#include <anticarium_pi/AnticariumManager.h>

WeatherEmulator::WeatherEmulator(const shared_types::Control& control, QObject* parent) : QObject(parent) {
    this->control = control;
}

void WeatherEmulator::run() {
}

shared_types::SensorData WeatherEmulator::getSensorData() const {
    return shared_types::SensorData(); // TODO change to real object
}

void WeatherEmulator::setControl(const shared_types::Control& control) {
    this->control = control;
}

WeatherEmulator::~WeatherEmulator() {
}
