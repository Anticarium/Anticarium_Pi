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

void AnticariumManager::initializeI2c() {
    // TODO: Add values for parameters
    I2CSlaveParameters inputParameters;
    I2CSlaveParameters outputParameters;

    i2cOutput = new I2COutput(outputParameters, this);
    i2cInput  = new I2CInput(1000, inputParameters, this);
}

void AnticariumManager::connectI2c() {
    i2cOutput->connectI2c();
    i2cInput->connectI2c();
}
