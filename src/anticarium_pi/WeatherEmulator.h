#pragma once
#include <QObject>
#include <shared_types/Control.h>
#include <shared_types/SensorData.h>

class WeatherEmulator : public QObject {
    Q_OBJECT
  public:
    WeatherEmulator(const shared_types::Control& control, QObject* parent = nullptr);
    void run();
    shared_types::SensorData getSensorData() const;
    void setControl(const shared_types::Control& control);
    virtual ~WeatherEmulator();

  private:
    shared_types::Control control;
};
