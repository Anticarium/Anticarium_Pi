#pragma once
#include <QObject>
#include <linux/i2c-dev.h>
#include <shared_types/SensorData.h>
#include <sys/ioctl.h>

class I2cTalker : public QObject {
    Q_OBJECT
  public:
    I2cTalker();
    enum OutputType { LED, FAN, HEAT, WATER };
    void output(OutputType outputType);
    shared_types::SensorData fetchSensorData();

    virtual ~I2cTalker();

  private:
    enum Member { OUTPUT_MCU, INPUT_MCU };
};
