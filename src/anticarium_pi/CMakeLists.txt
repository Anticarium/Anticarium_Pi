set(HEADER_FILES
    anticarium_pi/AnticariumManager.h
    anticarium_pi/WeatherEmulator.h
    anticarium_pi/WeatherManager.h
    anticarium_pi/helper/AnticariumFunctions.hpp
    anticarium_pi/i2c_members/I2CSlave.h
    anticarium_pi/i2c_members/I2CInput.h
    anticarium_pi/i2c_members/I2COutput.h
    anticarium_pi/Jttp.h
)

set(SOURCE_FILES
    anticarium_pi/AnticariumManager.cpp
    anticarium_pi/WeatherEmulator.cpp
    anticarium_pi/WeatherManager.cpp
    anticarium_pi/i2c_members/I2CSlave.cpp
    anticarium_pi/i2c_members/I2CInput.cpp
    anticarium_pi/i2c_members/I2COutput.cpp
    anticarium_pi/Jttp.cpp
)

set(TARGET_NAME anticarium_pi_lib)

include(ExternLibs)

add_library(${TARGET_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/pid
    ${CMAKE_SOURCE_DIR}/src/config
    ${CMAKE_SOURCE_DIR}/src/anticarium_pi
)

target_link_libraries(${TARGET_NAME} PRIVATE
    anticarium_additional_libs
    anticarium_config_lib
)

ADDSHAREDTYPES(${TARGET_NAME})
ADDQT5CORE(${TARGET_NAME})
ADDJSON(${TARGET_NAME})
ADDSPDLOG(${TARGET_NAME})
ADDQT5NETWORK(${TARGET_NAME})
