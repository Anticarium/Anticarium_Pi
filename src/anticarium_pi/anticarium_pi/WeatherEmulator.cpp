#include <anticarium_pi/AnticariumManager.h>
#include <config/DynamicSettings.h>

static WeatherEmulator* weatherEmulator = nullptr;

template <>
void PIDController<double>::registerTimeFunction(unsigned long (*)());

template <>
void PIDController<double>::setTarget(double);

template <>
void PIDController<double>::tick();

static double temperatureFeedback() {
    return weatherEmulator->getCurrentTemperatureInt();
}

static void temperatureOutput(double output) {
    if (output > 0) {
        weatherEmulator->setHeat(true);
    } else {
        weatherEmulator->setHeat(false);
    }
}

static double moistureFeedback() {
    return weatherEmulator->getCurrentMoisture();
}

static void moistureOutput(double output) {
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

    const auto dynamicSettings       = DynamicSettings::instance();
    const auto& temperaturePIDValues = dynamicSettings->getTemperaturePID();

    temperaturePid = std::make_unique<PIDController<double>>(temperaturePIDValues.getP(), temperaturePIDValues.getI(), temperaturePIDValues.getD(),
                                                             temperatureFeedback, temperatureOutput);
    temperaturePid->registerTimeFunction(timeFunction);

    const auto& moisturePIDValues = dynamicSettings->getMoisturePID();

    moisturePid =
    std::make_unique<PIDController<double>>(moisturePIDValues.getP(), moisturePIDValues.getI(), moisturePIDValues.getD(), moistureFeedback, moistureOutput);
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

    auto dynamicSettings      = DynamicSettings::instance();
    auto temperaturePIDValues = dynamicSettings->getTemperaturePID();

    temperaturePIDValues.setP(temperaturePid->getP());
    temperaturePIDValues.setI(temperaturePid->getI());
    temperaturePIDValues.setD(temperaturePid->getD());

    dynamicSettings->setTemperaturePID(temperaturePIDValues);

    return heat;
}

bool WeatherEmulator::calculateMoistureToggle(int currentMoisture) {
    this->currentMoisture = currentMoisture;
    moisturePid->tick();

    auto dynamicSettings   = DynamicSettings::instance();
    auto moisturePIDValues = dynamicSettings->getMoisturePID();

    moisturePIDValues.setP(moisturePid->getP());
    moisturePIDValues.setI(moisturePid->getI());
    moisturePIDValues.setD(moisturePid->getD());

    dynamicSettings->setMoisturePID(moisturePIDValues);

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
    weatherEmulator = nullptr;
}
