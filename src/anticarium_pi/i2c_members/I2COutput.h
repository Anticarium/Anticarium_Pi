#pragma once
#include <anticarium_pi/i2c_members/I2CSlave.h>

class I2COutput : public I2CSlave {
  public:
    I2COutput(const I2CSlaveParameters& parameters, QObject* parent = nullptr);
    enum OutputType { LED, FAN, HEAT, WATER };
    /*
     * Writes data according to specified protocol in Anticarium_IC README
     * Returns false if failed and true if succeeded
     */
    bool send(OutputType outputType, unsigned char value);
    virtual ~I2COutput();
};
