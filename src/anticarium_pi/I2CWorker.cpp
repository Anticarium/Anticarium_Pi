#include <anticarium_pi/I2CWorker.h>
#include <fcntl.h>         //Needed for I2C port
#include <linux/i2c-dev.h> //Needed for I2C port
#include <memory>
#include <sys/ioctl.h> //Needed for I2C port
#include <unistd.h>    //Needed for I2C port

I2CWorker::I2CWorker(const I2CWorkerParameters& outputParameters, const I2CWorkerParameters& inputParameters, QObject* parent)
: QObject(parent), OUTPUT_PARAMETERS(outputParameters), INPUT_PARAMETERS(inputParameters) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &I2CWorker::fetchData);
}

bool I2CWorker::connectI2c(int timeout) {
    // Open I2c bus
    i2cFile = open(FILE_NAME.data(), O_RDWR);
    if (i2cFile < 0) {
        return false;
    }

    int outputConnectionCode = ioctl(i2cFile, I2C_SLAVE, OUTPUT_PARAMETERS.address);
    int inputConnectionCode  = ioctl(i2cFile, I2C_SLAVE, INPUT_PARAMETERS.address);
    if (outputConnectionCode < 0 || inputConnectionCode < 0) {
        return false;
    }

    timer->start(timeout);
    return true;
}

shared_types::SensorData I2CWorker::getSensorData() {
    return sensorData;
}

void I2CWorker::fetchData() {
    std::unique_ptr<unsigned char[]> buffer = std::make_unique<unsigned char[]>(INPUT_PARAMETERS.bufferSize);

    int bytesRead = read(i2cFile, buffer.get(), INPUT_PARAMETERS.bufferSize);
    if (bytesRead == static_cast<int>(INPUT_PARAMETERS.bufferSize)) // read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
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


int I2CWorker::convertMoisture(int value) {
    // map using linear interpolation
    int result = ((value - MIN_ANALOG_MOISTURE) / (MAX_ANALOG_MOISTURE - MIN_ANALOG_MOISTURE)) * 100;
    return result;
}

bool I2CWorker::send(I2CWorker::OutputType outputType, unsigned char value) {
    std::unique_ptr<unsigned char[]> buffer = std::make_unique<unsigned char[]>(OUTPUT_PARAMETERS.bufferSize);

    buffer[0] = outputType;
    buffer[1] = value;

    int bytesWritten = write(i2cFile, buffer.get(), OUTPUT_PARAMETERS.bufferSize);

    return bytesWritten == static_cast<int>(OUTPUT_PARAMETERS.bufferSize);
}

I2CWorker::~I2CWorker() {
}
