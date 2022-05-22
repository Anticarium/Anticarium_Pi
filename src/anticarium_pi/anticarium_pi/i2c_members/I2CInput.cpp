#include <anticarium_pi/helper/AnticariumFunctions.hpp>
#include <anticarium_pi/i2c_members/I2CInput.h>
#include <fcntl.h>         //Needed for I2C port
#include <linux/i2c-dev.h> //Needed for I2C port
#include <memory>
#include <sys/ioctl.h> //Needed for I2C port
#include <unistd.h>    //Needed for I2C port
#include <spdlog/spdlog.h>

I2CInput::I2CInput(const I2CSlaveParameters& params, QObject* parent) : I2CSlave(params, parent) {
}

const shared_types::SensorData& I2CInput::getSensorData() const {
    return sensorData;
}

void I2CInput::fetchData() {
    auto buffer = std::make_unique<unsigned char[]>(params.bufferSize);

    const int bytesRead = read(file, buffer.get(), params.bufferSize);
    if (bytesRead == static_cast<int>(params.bufferSize)) // read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
    {
        // First byte indicates data type
        auto value = *reinterpret_cast<float*>(buffer.get() + 1);

        switch (buffer[0]) {
            case 't': {
                sensorData.setTemperature(value);
            } break;
            case 'h': {
                sensorData.setHumidity(static_cast<int>(value));
            } break;
            case 'm': {
                value = map<int>(static_cast<int>(value), maxAnalogMoisture, minAnalogMoisture, minPercentage, maxPercentage);

                // There are cases where map outputs bigger value by 1
                if (value > maxPercentage) {
                    value = maxPercentage;
                }
                sensorData.setMoisture(static_cast<int>(value));
            } break;
            default: {
            } break;
        }
    } else {
        SPDLOG_ERROR("Failed to read i2c data");
    }
}
