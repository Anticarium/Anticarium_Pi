#pragma once
#include <QObject>

struct I2CSlaveParameters {
    int address       = 0;
    size_t bufferSize = 0;
};

class I2CSlave : public QObject {
    Q_OBJECT
  public:
    I2CSlave(const I2CSlaveParameters& parameters, QObject* parent = nullptr);

    /*
     * Connects to I2C slave
     * Returns true if connected, and false if failed to connect
     */
    bool connectI2c();
    virtual ~I2CSlave();

  protected:
    int file = 0;
    const I2CSlaveParameters params;

    const unsigned char minPercentage = 0;
    const unsigned char maxPercentage = 100;

  private:
    const std::string fileName = "/dev/i2c-1";
};
