#pragma once
#include <anticarium_pi/WeatherEmulator.h>

class AnticariumManager : public QObject {
    Q_OBJECT
  public:
    AnticariumManager(QObject* parent = nullptr);
    void run();
    virtual ~AnticariumManager();

  private:
    WeatherEmulator* weatherEmulator = nullptr;
};
