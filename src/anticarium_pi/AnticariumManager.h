#pragma once
#include <anticarium_pi/I2CWorker.h>
#include <anticarium_pi/WeatherManager.h>

class AnticariumManager : public QObject {
    Q_OBJECT
  public:
    AnticariumManager(QObject* parent = nullptr);
    void run();
    virtual ~AnticariumManager();

  private:
    WeatherManager* weatherManager = nullptr;
    I2CWorker* i2cWorker           = nullptr;
};
