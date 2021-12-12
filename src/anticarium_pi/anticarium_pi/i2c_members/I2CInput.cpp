#include <anticarium_pi/helper/AnticariumFunctions.hpp>
#include <anticarium_pi/i2c_members/I2CInput.h>
#include <fcntl.h>         //Needed for I2C port
#include <linux/i2c-dev.h> //Needed for I2C port
#include <memory>
#include <spdlog/spdlog.h>
#include <sys/ioctl.h> //Needed for I2C port
#include <unistd.h>    //Needed for I2C port

I2CInput::I2CInput(const I2CSlaveParameters& parameters, QObject* parent) : I2CSlave(parameters, parent) {
}

shared_types::SensorData I2CInput::getSensorData() {
    return sensorData;
}

void I2CInput::fetchData() {
    std::unique_ptr<unsigned char[]> buffer = std::make_unique<unsigned char[]>(PARAMETERS.bufferSize);

    int bytesRead = read(file, buffer.get(), PARAMETERS.bufferSize);
    if (bytesRead == static_cast<int>(PARAMETERS.bufferSize)) // read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
    {
        int value = buffer[2] << 8;
        value |= buffer[1];

        switch (buffer[0]) {
        case 't': {
            sensorData.setTemperature(value);
        } break;
        case 'h': {
            sensorData.setHumidity(value);
        } break;
        case 'm': {
            int mappedMoisture = map<int>(value, MIN_ANALOG_MOISTURE, MAX_ANALOG_MOISTURE, 0, 100);
            sensorData.setMoisture(mappedMoisture);
        } break;
        default: { } break; }
    }
}

I2CInput::~I2CInput() {
}
