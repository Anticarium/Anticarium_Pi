# Anticarium_Pi

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