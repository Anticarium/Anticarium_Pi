#include <anticarium_pi/i2c_members/I2CInput.h>
#include <fcntl.h>         //Needed for I2C port
#include <linux/i2c-dev.h> //Needed for I2C port
#include <memory>
#include <sys/ioctl.h> //Needed for I2C port
#include <unistd.h>    //Needed for I2C port

I2CInput::I2CInput(int timeout, const I2CSlaveParameters& parameters, QObject* parent) : I2CSlave(parameters, parent) {
    timer = new QTimer(this);
    timer->setInterval(timeout);
    connect(timer, &QTimer::timeout, this, &I2CInput::fetchData);
}

bool I2CInput::connectI2c() {
    bool connected = I2CSlave::connectI2c();
    if (connected) {
        timer->start();
    }
    return connected;
}

shared_types::SensorData I2CInput::getSensorData() {
    return sensorData;
}

void I2CInput::fetchData() {
    std::unique_ptr<unsigned char[]> buffer = std::make_unique<unsigned char[]>(BUFFER_SIZE);

    int bytesRead = read(file, buffer.get(), BUFFER_SIZE);
    if (bytesRead == static_cast<int>(BUFFER_SIZE)) // read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
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
            sensorData.setMoisture(convertMoisture(value));
        } break;
        default: { } break; }
    }
}

int I2CInput::convertMoisture(int value) {
    // map using linear interpolation
    int result = ((value - MIN_ANALOG_MOISTURE) / (MAX_ANALOG_MOISTURE - MIN_ANALOG_MOISTURE)) * 100;
    return result;
}
