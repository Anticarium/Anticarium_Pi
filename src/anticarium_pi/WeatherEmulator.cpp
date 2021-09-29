#include <anticarium_pi/AnticariumManager.h>

static WeatherEmulator* weatherEmulator = nullptr;

static float temperatureFeedback() {
    return weatherEmulator->getSensorData().getTemperature();
}

static void temperatureOutput(float output) {
    if (output > 0) {
        weatherEmulator->heat(true);
    } else {
        weatherEmulator->heat(false);
    }
}

static unsigned long timeFunction() {
    std::chrono::time_point now          = std::chrono::system_clock::now();
    std::chrono::duration timeSinceEpoch = now.time_since_epoch();
    std::chrono::duration millis         = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch);
    long long count                      = millis.count();
    return static_cast<unsigned long>(count);
}

WeatherEmulator::WeatherEmulator(const shared_types::Control& control, QObject* parent) : QObject(parent) {
    weatherEmulator = this;
    temperaturePid  = std::make_unique<PIDController<float>>(1, 1, 1, temperatureFeedback, temperatureOutput);
    temperaturePid->registerTimeFunction(timeFunction);

    sampleTimer = new QTimer(this);
    connect(sampleTimer, &QTimer::timeout, this, &WeatherEmulator::sample);
    sampleTimer->setInterval(SAMPLE_TIMEOUT);

    setControl(control);
}

void WeatherEmulator::run() {
    // sample for first time before timer
    sample();

    sampleTimer->start();
}

shared_types::SensorData WeatherEmulator::getSensorData() const {
    return shared_types::SensorData(); // TODO change to real object
}

void WeatherEmulator::setControl(const shared_types::Control& control) {
    this->control = control;
    temperaturePid->setTarget(control.getTemperature());
}

void WeatherEmulator::heat(bool set) {
}

void WeatherEmulator::sample() {
    temperaturePid->tick();
}

WeatherEmulator::~WeatherEmulator() {
}
