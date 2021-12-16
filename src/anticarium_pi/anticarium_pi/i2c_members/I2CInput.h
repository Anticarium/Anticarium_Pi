#pragma once
#include <anticarium_pi/i2c_members/I2CSlave.h>
#include <shared_types/SensorData.h>

class I2CInput : public I2CSlave {
    Q_OBJECT
  public:
    I2CInput(const I2CSlaveParameters& parameters, QObject* parent = nullptr);
    shared_types::SensorData getSensorData();

    virtual ~I2CInput();
  public slots:
    /*
     * Reads value from i2c and writes it to sensorData variable
     */
    void fetchData();

  private:
    shared_types::SensorData sensorData;

    const int MIN_ANALOG_MOISTURE = 17;
    const int MAX_ANALOG_MOISTURE = 1023;
};
