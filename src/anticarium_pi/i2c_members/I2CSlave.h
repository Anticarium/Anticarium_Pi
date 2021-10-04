#pragma once
#include <QObject>

struct I2CSlaveParameters {
    std::string fileName = "";
    int file             = 0;
    int fileAction       = 0;
    int address          = 0;
    size_t bufferSize    = 4;
};

class I2CSlave : public QObject {
    Q_OBJECT
  public:
    I2CSlave(const I2CSlaveParameters& parameters, QObject* parent = nullptr);

    /*
     * Connects to I2C slave
     * Returns true if connected, and false if failed to connect
     */
    bool connect();

    virtual ~I2CSlave();

  protected:
    int file = 0;
    const size_t BUFFER_SIZE;

  private:
    const std::string FILE_NAME;
    const int FILE_ACTION;
    const int ADDRESS;
};
