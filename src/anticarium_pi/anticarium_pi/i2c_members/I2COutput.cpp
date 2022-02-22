#include <anticarium_pi/helper/AnticariumFunctions.hpp>
#include <anticarium_pi/i2c_members/I2COutput.h>
#include <fcntl.h>         //Needed for I2C port
#include <linux/i2c-dev.h> //Needed for I2C port
#include <memory>
#include <spdlog/spdlog.h>
#include <sys/ioctl.h> //Needed for I2C port
#include <unistd.h>    //Needed for I2C port

I2COutput::I2COutput(const I2CSlaveParameters& parameters, QObject* parent) : I2CSlave(parameters, parent) {
}

bool I2COutput::send(OutputType outputType, unsigned char value) const {
    auto buffer = std::make_unique<unsigned char[]>(params.bufferSize);

    buffer[0] = outputType;
    buffer[1] = processValue(outputType, value);

    const int bytesWritten = write(file, buffer.get(), params.bufferSize);

    SPDLOG_INFO(QString("Output type: %1, Value: %2").arg(outputType).arg(value).toStdString());
    return bytesWritten == static_cast<int>(params.bufferSize);
}

unsigned char I2COutput::processValue(I2COutput::OutputType outputType, unsigned char value) const {
    using Byte = std::numeric_limits<unsigned char>;

    switch (outputType) {
        case I2COutput::FAN_PWM: {
            // For fan to stop rotating we need to send pwm of 0, which will be
            // inverted on IC side to max pwm and for some reason stop the fan with disabled
            // power
            if (value) {
                value = map<unsigned char>(value, minPercentage, maxPercentage, Byte::max(), Byte::min());
            }
        } break;
        case I2COutput::LED: {
            value = map<unsigned char>(value, minPercentage, maxPercentage, Byte::min(), Byte::max());
        } break;
        case I2COutput::HEAT: {
            value = !value;
        } break;
        default: {
        } break;
    }

    return value;
}
