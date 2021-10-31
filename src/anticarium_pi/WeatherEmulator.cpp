#include <anticarium_pi/AnticariumManager.h>

static WeatherEmulator* weatherEmulator = nullptr;

static float temperatureFeedback() {
    return weatherEmulator->getCurrentTemperature();
}
#include <QDebug>
static void temperatureOutput(float output) {
    if (output > 0) {
        weatherEmulator->setHeat(true);
    } else {
        weatherEmulator->setHeat(false);
    }
}

static int moistureFeedback() {
    return weatherEmulator->getCurrentMoisture();
}

static void moistureOutput(int output) {
    if (output > 0) {
        weatherEmulator->setWater(true);
    } else {
        weatherEmulator->setWater(false);
    }
}

static unsigned long timeFunction() {
    std::chrono::time_point now          = std::chrono::system_clock::now();
    std::chrono::duration timeSinceEpoch = now.time_since_epoch();
    std::chrono::duration millis         = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch);
    long long count                      = millis.count();
    return static_cast<unsigned long>(count);
}

WeatherEmulator::WeatherEmulator(QObject* parent) : QObject(parent) {
    weatherEmulator = this;
    temperaturePid  = std::make_unique<PIDController<float>>(1, 1, 1, temperatureFeedback, temperatureOutput);
    temperaturePid->registerTimeFunction(timeFunction);
    moisturePid = std::make_unique<PIDController<int>>(1, 1, 1, moistureFeedback, moistureOutput);
    moisturePid->registerTimeFunction(timeFunction);
}

void WeatherEmulator::setTargetTemperature(float targetTemperature) {
    temperaturePid->setTarget(targetTemperature);
}

void WeatherEmulator::setTargetMoisture(int targetMoisture) {
    moisturePid->setTarget(targetMoisture);
}

bool WeatherEmulator::calculateHeatToggle(float currentTempearture) {
    this->currentTemperature = currentTempearture;
    temperaturePid->tick();
    return heat;
}

bool WeatherEmulator::calculateMoistureToggle(int currentMoisture) {
    this->currentMoisture = currentMoisture;
    moisturePid->tick();
    return water;
}

void WeatherEmulator::setHeat(bool heat) {
    this->heat = heat;
}

void WeatherEmulator::setWater(bool water) {
    this->water = water;
}

float WeatherEmulator::getCurrentTemperature() {
    return currentTemperature;
}

int WeatherEmulator::getCurrentMoisture() {
    return currentMoisture;
}

WeatherEmulator::~WeatherEmulator() {
}
