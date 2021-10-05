#include <anticarium_pi/AnticariumManager.h>
#include <anticarium_pi/config/ApplicationSettings.h>

AnticariumManager::AnticariumManager(QObject* parent) : QObject(parent) {
    ApplicationSettings* settings = ApplicationSettings::instance();

    weatherManager = new WeatherManager(settings->getControl(), this);
}

void AnticariumManager::run() {
    weatherManager->run();
}

AnticariumManager::~AnticariumManager() {
}
