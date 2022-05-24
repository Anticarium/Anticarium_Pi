# Anticarium_Pi

- ADD: Setup scripts for Ubuntu 20.04 development VM and Raspberry Pi for first time setup in `setup` directory
- ADD: pi.py script for remote compiling and interfacing with Raspberry pi using ssh
- MODIFY: Forcefully disable watering if moisture was set to 0, due to PID expecting the sensor value to rise
- MODIFY: Horizontally mirrored video output because camera physically is rotated
- MODIFY: Changed minimum analog moisture value from 17 to 0
- ADD: Incorrect temperature value handling before calculating heat PID
- ADD: Unhandled exception handler for anticarium_pi and camera applications
- ADD: Different output values from WeatherManager for different electronic components
- ADD: `FAN_IO` OutputType for enabling or disabling fan entirely
- ADD: `UDP_Threads_Amount` parameter in `settings.ini` to regulate thread amount for UDP sending
- ADD: Multithreaded UDP image sending by splitting image into several parts
- MODIFY: Fixed first values of temperature PID 
- ADD: UDP heartbeat to stop image sending if there is no active client
- REMOVE: UDP handshake
- ADD: `ImageProcess::build` tests
- MODIFY: Changed endianness of sending image row
- MODIFY: Updated logger formatter with constant spaces for every log part
- MODIFY: Rotate log file when it is bigger than 1MB 
- ADD: Log level parameter in `settings.ini` 
- MODIFY: Changed image color format to BGR

# 1.2.0
- ADD: UDP sender class `UDPSender`, that sends video to UDP
- ADD: UDP receiver class `UDPListener`, that decides which client to send data to
- ADD: Raspicam library
- ADD: `camera_app` that reads data from camera and sends it using UDP
- MODIFY: Remade project structure to include new `camera_app` build
- MODIFY: Moved `config` folder outside `anticarium_pi`, to be shared between `anticarium_pi` and `anticarium_camera` apps
- ADD: Structure for camera app development
- MODIFY: Create log file path from QApplication::applicationDirPath()
- REMOVE: `VersionConfig.h.in` file and cmake script, because it is unused
- ADD: `settings.ini.h` gets copied to build directory as `settings.ini` to become real application settings
- ADD: Application settings class `ApplicationSettings` along with its tests
- ADD: `Anticarium_Server_URL` setting that stores URL to which to make requests
- ADD: `Sensor_Data_send_timeout` setting for sensor data sending to server
- ADD: `Control_Data_fetch_timeout` setting for control data fetching from server
- ADD: `PID_sample_timeout` setting for PID sampling
- ADD: `I2C_fetch_timeout` setting for fetching data from input MCU
- MODIFY: Changed http response header to "Anticarium_content_description"

## 1.1.0
- ADD: Request Control on app startup
- REMOVE: ApplicationSettings and its tests
- MODIFY: shared_types v1.3.0
- MODIFY: AnticariumManager now reads and sends data to server
- ADD: JTTP class to communicate with server
- ADD: Setup guide in `README.md`
- ADD: Logger, logs under `./log/` relative to program executable
- ADD: Spdlog HunterGate package
- ADD: I2C output from WeatherManager
- ADD: I2C input and output classes

## 1.0.0
- ADD: WeatherManager for managing WeatherEmulator and upcomming I2C communication object
- ADD: Temperature and moisture PIDs
- ADD: PID library https://github.com/nicholastmosher/PID
- ADD: `libs` folder for libraries 
- MODIFY: Changed tests CMake structure to be just like in rest of the project
- ADD: WeatherEmulator class for managing PIDs
- ADD: ApplicationManager as main class for anticarium_pi
- ADD: ApplicationSettings class and its tests
- MODIFY: Put `main.cpp` under `apps/server_app` according to correct cmake structure
- REMOVE: `tests/io_tests`
- REMOVE: `tests/dht11_tests`
- ADD: Anticarium Shared types v1.1.4
- MODIFY: Moved `main.cpp` to `apps/server_app`
- ADD: `cmake` folder for CMake scripts (includes `ExternLibs.cmake` and `HunterGate.cmake`)
- ADD: `HunterGate` package manager
