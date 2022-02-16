#include <anticarium_pi/helper/AnticariumFunctions.hpp>
#include <anticarium_pi/i2c_members/I2CInput.h>
#include <fcntl.h>         //Needed for I2C port
#include <linux/i2c-dev.h> //Needed for I2C port
#include <memory>
#include <sys/ioctl.h> //Needed for I2C port
#include <unistd.h>    //Needed for I2C port

I2CInput::I2CInput(const I2CSlaveParameters& params, QObject* parent) : I2CSlave(params, parent) {
}

shared_types::SensorData I2CInput::getSensorData() {
    return sensorData;
}

void I2CInput::fetchData() {
    auto buffer = std::make_unique<unsigned char[]>(params.bufferSize);

    int bytesRead = read(file, buffer.get(), params.bufferSize);
    if (bytesRead == static_cast<int>(params.bufferSize)) // read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
    {
        auto value = *reinterpret_cast<float*>(buffer.get() + 1);

        switch (buffer[0]) {
            case 't': {
                sensorData.setTemperature(value);
            } break;
            case 'h': {
                sensorData.setHumidity(static_cast<int>(value));
            } break;
            case 'm': {
                int mappedMoisture = map<int>(static_cast<int>(value), maxAnalogMoisture, minAnalogMoisture, 0, 100);
                sensorData.setMoisture(mappedMoisture);
            } break;
            default: {
            } break;
        }
    }
}
