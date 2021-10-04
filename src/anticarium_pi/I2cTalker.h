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
    void output(OutputType outputType, int value);
    shared_types::SensorData getSensorData();

    virtual ~I2cTalker();

  private:
    enum Member { OUTPUT_MCU, INPUT_MCU };
    int inputFile           = 0;
    int outputFile          = 0;
    const int OUTPUT_LENGTH = 2;
    unsigned char buffer[2] = { 0 };
    std::string outputFileName;
    std::string inputFileName;
};
