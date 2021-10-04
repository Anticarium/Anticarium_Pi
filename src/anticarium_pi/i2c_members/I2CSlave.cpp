#include <anticarium_pi/i2c_members/I2CSlave.h>
#include <fcntl.h>         //Needed for I2C port
#include <linux/i2c-dev.h> //Needed for I2C port
#include <sys/ioctl.h>     //Needed for I2C port
#include <unistd.h>        //Needed for I2C port


I2CSlave::I2CSlave(const I2CSlaveParameters& parameters, QObject* parent)
: QObject(parent), FILE_NAME(parameters.fileName), FILE_ACTION(parameters.fileAction), ADDRESS(parameters.address), BUFFER_SIZE(parameters.bufferSize) {
}

bool I2CSlave::connect() {
    // Open I2c bus
    file = open(FILE_NAME.data(), FILE_ACTION);
    if (file < 0) {
        return false;
    }

    int connectionCode = ioctl(file, I2C_SLAVE, ADDRESS);
    if (connectionCode < 0) {
        return false;
    }
    return true;
}

I2CSlave::~I2CSlave() {
}
