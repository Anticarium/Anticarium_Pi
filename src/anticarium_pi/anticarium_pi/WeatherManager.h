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
    void run();

    shared_types::SensorData getSensorData() const;

    /*
     * Uses control data as new targets for PIDs
     */
    void setControl(const shared_types::Control& control);

    virtual ~WeatherManager();

  private:
    WeatherEmulator* weatherEmulator = nullptr;

    QTimer* sampleTimer   = nullptr;
    QTimer* i2cFetchTimer = nullptr;

    /*
     * Sample sensor data and output according to PIDs
     */
    void sample();

    /*
     * Changes input value according to different requirements of output components
     * and sends it to i2c
     */
    void send(I2COutput::OutputType outputType, int value);

    I2CInput* i2cInput   = nullptr;
    I2COutput* i2cOutput = nullptr;
};
