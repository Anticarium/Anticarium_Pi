# Anticarium_Pi

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