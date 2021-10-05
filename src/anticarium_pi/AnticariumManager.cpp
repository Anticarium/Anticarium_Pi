#include <anticarium_pi/AnticariumManager.h>
#include <anticarium_pi/config/ApplicationSettings.h>

AnticariumManager::AnticariumManager(QObject* parent) : QObject(parent) {
    ApplicationSettings* settings = ApplicationSettings::instance();

    weatherManager = new WeatherManager(settings->getControl(), this);

    I2CWorkerParameters outputParameters;
    outputParameters.address    = 0;
    outputParameters.bufferSize = 2;
    I2CWorkerParameters inputParameters;
    inputParameters.address    = 1;
    inputParameters.bufferSize = 3;

    i2cWorker = new I2CWorker(outputParameters, inputParameters, this);
}

void AnticariumManager::run() {
    i2cWorker->connectI2c(1000);
    weatherManager->run();
}

AnticariumManager::~AnticariumManager() {
}
