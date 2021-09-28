#include <anticarium_pi/AnticariumManager.h>
#include <anticarium_pi/config/ApplicationSettings.h>

AnticariumManager::AnticariumManager(QObject* parent) : QObject(parent) {
    ApplicationSettings* settings = ApplicationSettings::instance();

    weatherEmulator = new WeatherEmulator(settings->getControl(), this);
}

void AnticariumManager::run() {
    weatherEmulator->run();
}

AnticariumManager::~AnticariumManager() {
}
