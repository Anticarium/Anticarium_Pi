# Anticarium_Pi

- MODIFY: Changed tests CMake structure to be just like in rest of the project
- ADD: WeatherEmulator class for managing PIDs
- ADD: ApplicationManager as main class for anticarium_pi
- ADD: ApplicationSettings class and its tests
- MODIFY: Put `main.cpp` under `apps/server_app` according to correct cmake structure
- REMOVE: `tests/io_tests`
- REMOVE: `tests/dht11_tests`
- ADD: Anticarium Shared types
- ADD: `HunterGate` package manager
- MODIFY: Moved `main.cpp` to `apps/server_app`
- ADD: `cmake` folder for CMake scripts (includes `ExternLibs.cmake`)