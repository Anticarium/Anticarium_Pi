#pragma once
#include <anticarium_pi/WeatherManager.h>
#include <anticarium_pi/i2c_members/I2CInput.h>
#include <anticarium_pi/i2c_members/I2COutput.h>

class AnticariumManager : public QObject {
    Q_OBJECT
  public:
    AnticariumManager(QObject* parent = nullptr);
    void run();
    virtual ~AnticariumManager();

  private:
    WeatherManager* weatherManager = nullptr;
    I2COutput* i2cOutput           = nullptr;
    I2CInput* i2cInput             = nullptr;

    void initializeI2c();
    void connectI2c();
};
