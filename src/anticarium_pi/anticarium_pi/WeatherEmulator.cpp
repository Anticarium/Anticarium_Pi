#include <anticarium_pi/AnticariumManager.h>

static WeatherEmulator* weatherEmulator = nullptr;

template <>
void PIDController<int>::registerTimeFunction(unsigned long (*)());

template <>
void PIDController<int>::setTarget(int);

template <>
void PIDController<int>::tick();

static int temperatureFeedback() {
    return weatherEmulator->getCurrentTemperatureInt();
}

static void temperatureOutput(int output) {
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
    const auto now            = std::chrono::system_clock::now();
    const auto timeSinceEpoch = now.time_since_epoch();
    const auto millis         = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch);
    long long count           = millis.count();
    return static_cast<unsigned long>(count);
}

WeatherEmulator::WeatherEmulator(QObject* parent) : QObject(parent) {
    weatherEmulator = this;
    temperaturePid  = std::make_unique<PIDController<int>>(1, 1, 1, temperatureFeedback, temperatureOutput);
    temperaturePid->registerTimeFunction(timeFunction);
    moisturePid = std::make_unique<PIDController<int>>(1, 1, 1, moistureFeedback, moistureOutput);
    moisturePid->registerTimeFunction(timeFunction);
}

void WeatherEmulator::setTargetTemperature(float targetTemperature) {
    int intTemperature = static_cast<int>(targetTemperature * FLOAT_MULTIPLIER);
    temperaturePid->setTarget(intTemperature);
}

void WeatherEmulator::setTargetMoisture(int targetMoisture) {
    moisturePid->setTarget(targetMoisture);
}

bool WeatherEmulator::calculateHeatToggle(float currentTempearture) {
    this->currentTemperature = static_cast<int>(currentTempearture * FLOAT_MULTIPLIER);
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

int WeatherEmulator::getCurrentTemperatureInt() {
    return currentTemperature;
}

int WeatherEmulator::getCurrentMoisture() {
    return currentMoisture;
}

WeatherEmulator::~WeatherEmulator() {
}
