#include <anticarium_pi/i2c_members/I2COutput.h>
#include <fcntl.h>         //Needed for I2C port
#include <linux/i2c-dev.h> //Needed for I2C port
#include <memory>
#include <sys/ioctl.h> //Needed for I2C port
#include <unistd.h>    //Needed for I2C port


I2COutput::I2COutput(const I2CSlaveParameters& parameters, QObject* parent) : I2CSlave(parameters, parent) {
}

bool I2COutput::send(I2COutput::OutputType outputType, unsigned char value) {
    std::unique_ptr<unsigned char[]> buffer = std::make_unique<unsigned char[]>(BUFFER_SIZE);

    buffer[0] = outputType;
    buffer[1] = value;

    bool bytesWritten = write(file, buffer.get(), BUFFER_SIZE);

    return bytesWritten == BUFFER_SIZE;
}

I2COutput::~I2COutput() {
}
