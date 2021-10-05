#pragma once
#include <QObject>
#include <shared_types/SensorData.h>

struct I2CWorkerParameters {
    int address       = 0;
    size_t bufferSize = 4;
};

class I2CWorker : public QObject {
    Q_OBJECT
  public:
    I2CWorker(const I2CWorkerParameters& outputParameters, const I2CWorkerParameters& inputParameters, QObject* parent = nullptr);
    shared_types::SensorData getSensorData();

    /*
     * Connects to I2C slave
     * Pass input fetch timeout
     * Returns true if connected, and false if failed to connect
     */
    bool connectI2c();

    enum OutputType { LED = 2, FAN = 3, HEAT = 9, WATER = 10 };

    /*
     * Writes data according to specified protocol in Anticarium_IC README
     * Returns false if failed and true if succeeded
     */
    bool send(OutputType outputType, unsigned char value);

    virtual ~I2CWorker();

  public slots:
    /*
     * Reads value from i2c and writes it to sensorData variable
     */
    void fetchData();

  private:
    int i2cFile = 0;

    const I2CWorkerParameters OUTPUT_PARAMETERS;
    const I2CWorkerParameters INPUT_PARAMETERS;

    shared_types::SensorData sensorData;

    const int MIN_ANALOG_MOISTURE = 17;
    const int MAX_ANALOG_MOISTURE = 1023;

    const std::string FILE_NAME = "/dev/i2c-1";
};
