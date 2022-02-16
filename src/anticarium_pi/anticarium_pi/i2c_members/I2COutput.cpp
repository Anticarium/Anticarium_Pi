#include <anticarium_pi/i2c_members/I2COutput.h>
#include <fcntl.h>         //Needed for I2C port
#include <linux/i2c-dev.h> //Needed for I2C port
#include <memory>
#include <spdlog/spdlog.h>
#include <sys/ioctl.h> //Needed for I2C port
#include <unistd.h>    //Needed for I2C port

I2COutput::I2COutput(const I2CSlaveParameters& parameters, QObject* parent) : I2CSlave(parameters, parent) {
}

bool I2COutput::send(OutputType outputType, unsigned char value) {
    auto buffer = std::make_unique<unsigned char[]>(params.bufferSize);

    buffer[0] = outputType;
    buffer[1] = value;

    int bytesWritten = write(file, buffer.get(), params.bufferSize);

    SPDLOG_INFO(QString("Output type: %1, Value: %2").arg(outputType).arg(value).toStdString());
    return bytesWritten == static_cast<int>(params.bufferSize);
}
