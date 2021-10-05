#include <anticarium_pi/AnticariumManager.h>
#include <anticarium_pi/config/ApplicationSettings.h>

AnticariumManager::AnticariumManager(QObject* parent) : QObject(parent) {
    weatherManager = new WeatherManager(this);
}

void AnticariumManager::run() {
    ApplicationSettings* settings = ApplicationSettings::instance();
    weatherManager->run(settings->getControl());
}

AnticariumManager::~AnticariumManager() {
}
