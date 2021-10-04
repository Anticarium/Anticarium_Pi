#pragma once
#include <QTimer>
#include <anticarium_pi/i2c_members/I2CSlave.h>
#include <shared_types/SensorData.h>

class I2CInput : public I2CSlave {
    Q_OBJECT
  public:
    I2CInput(int timeout, const I2CSlaveParameters& parameters, QObject* parent = nullptr);
    shared_types::SensorData getSensorData();

    /*
     * Connects to i2c and starts fetching on success
     */
    bool connectI2c() override;
    virtual ~I2CInput();
  public slots:
    /*
     * Reads value from i2c and writes it to sensorData variable
     */
    void fetchData();

  private:
    shared_types::SensorData sensorData;
    QTimer* timer = nullptr;

    int convertMoisture(int value);

    const int MIN_ANALOG_MOISTURE = 17;
    const int MAX_ANALOG_MOISTURE = 1023;
};
