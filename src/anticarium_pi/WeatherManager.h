#pragma once
#include <QTimer>
#include <anticarium_pi/WeatherEmulator.h>
#include <anticarium_pi/i2c_members/I2CInput.h>
#include <anticarium_pi/i2c_members/I2COutput.h>
#include <shared_types/Control.h>
#include <shared_types/SensorData.h>

class WeatherManager : public QObject {
    Q_OBJECT
  public:
    WeatherManager(QObject* parent = nullptr);
    /*
     * Starts sampling timer
     */
    void run(const shared_types::Control& initialControl);

    shared_types::SensorData getSensorData() const;

    /*
     * Uses control data as new targets for PIDs
     */
    void setControl(const shared_types::Control& control);

    virtual ~WeatherManager();

  private:
    WeatherEmulator* weatherEmulator = nullptr;

    QTimer* sampleTimer         = nullptr;
    QTimer* i2cFetchTimer       = nullptr;
    const int I2C_FETCH_TIMEOUT = 500;
    const int SAMPLE_TIMEOUT    = 3000;

    /*
     * Sample sensor data and output according to PIDs
     */
    void sample();

    I2CInput* i2cInput   = nullptr;
    I2COutput* i2cOutput = nullptr;
};
