#pragma once
#include <anticarium_pi/i2c_members/I2CSlave.h>
#include <shared_types/SensorData.h>

class I2CInput : public I2CSlave {
    Q_OBJECT
  public:
    I2CInput(const I2CSlaveParameters& params, QObject* parent = nullptr);
    const shared_types::SensorData& getSensorData() const;

  public slots:
    /*
     * Reads value from i2c and writes it to sensorData variable
     */
    void fetchData();

  private:
    shared_types::SensorData sensorData;

    const int minAnalogMoisture = 0;
    const int maxAnalogMoisture = 1023;
};
