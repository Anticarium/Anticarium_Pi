#pragma once
#include <anticarium_pi/i2c_members/I2CSlave.h>

class I2COutput : public I2CSlave {
    Q_OBJECT
  public:
    I2COutput(const I2CSlaveParameters& parameters, QObject* parent = nullptr);
    enum OutputType { LED = 2, FAN = 3, HEAT = 9, WATER = 10 };
    /*
     * Writes data according to specified protocol in Anticarium_IC README
     * Returns false if failed and true if succeeded
     */
    bool send(OutputType outputType, unsigned char value);
    virtual ~I2COutput();
};