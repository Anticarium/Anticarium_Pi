#pragma once
#include <QTimer>
#include <anticarium_pi/WeatherEmulator.h>
#include <shared_types/Control.h>
#include <shared_types/SensorData.h>

class WeatherManager : public QObject {
  public:
    WeatherManager(const shared_types::Control& control, QObject* parent = nullptr);
    /*
     * Starts sampling timer
     */
    void run();

    shared_types::SensorData getSensorData() const;

    /*
     * Uses control data as new targets for PIDs
     */
    void setControl(const shared_types::Control& control);

    virtual ~WeatherManager();

  private:
    WeatherEmulator* weatherEmulator = nullptr;

    QTimer* sampleTimer      = nullptr;
    const int SAMPLE_TIMEOUT = 5000;

    /*
     * Sample sensor data and output according to PIDs
     */
    void sample();
};
