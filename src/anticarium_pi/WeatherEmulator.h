#pragma once
#include <QObject>
#include <QTimer>
#include <memory>
#include <pid/PID.h>
#include <shared_types/Control.h>
#include <shared_types/SensorData.h>

class WeatherEmulator : public QObject {
    Q_OBJECT
  public:
    WeatherEmulator(const shared_types::Control& control, QObject* parent = nullptr);

    /*
     * Starts sampling timer
     */
    void run();


    shared_types::SensorData getSensorData() const;

    /*
     * Sets this->control to new value
     * Takes this->control variable and uses its values as new targets for PIDs
     */
    void setControl(const shared_types::Control& control);

    /*
     * Tells to turn on/off the heating mat
     */
    void heat(bool set);

    virtual ~WeatherEmulator();

  private:
    shared_types::Control control;

    std::unique_ptr<PIDController<float>> temperaturePid;
    QTimer* sampleTimer      = nullptr;
    const int SAMPLE_TIMEOUT = 5000;

    /*
     * Sample sensor data and output according to PIDs
     */
    void sample();
};
