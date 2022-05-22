#include <anticarium_pi/i2c_members/I2CSlave.h>
#include <fcntl.h>         //Needed for I2C port
#include <linux/i2c-dev.h> //Needed for I2C port
#include <sys/ioctl.h>     //Needed for I2C port
#include <unistd.h>        //Needed for I2C port


I2CSlave::I2CSlave(const I2CSlaveParameters& parameters, QObject* parent) : QObject(parent), params(parameters) {
}

int I2CSlave::connectI2c() {
    // Open I2c bus
    file = open(fileName.data(), O_RDWR);

    const int connectionCode = ioctl(file, I2C_SLAVE, params.address);
    if (connectionCode == -1) {
        return errno;
    }

    return 0;
}

I2CSlave::~I2CSlave() {
}
