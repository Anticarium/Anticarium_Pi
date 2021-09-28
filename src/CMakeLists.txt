set(HEADER_FILES
    anticarium_pi/AnticariumManager.h
    anticarium_pi/WeatherEmulator.h
    anticarium_pi/config/ApplicationSettings.h
    )

set(SOURCE_FILES
    anticarium_pi/AnticariumManager.cpp
    anticarium_pi/WeatherEmulator.cpp
    anticarium_pi/config/ApplicationSettings.cpp
    )

set(TARGET_NAME anticarium_pi_lib)

include(ExternLibs)

add_library(${TARGET_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${TARGET_NAME} PRIVATE ${CURRENT_SOURCE_DIR})

ADDSHAREDTYPES(${TARGET_NAME})
ADDQT5CORE(${TARGET_NAME})
ADDJSON(${TARGET_NAME})
