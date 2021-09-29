set(HEADER_FILES
    anticarium_pi/AnticariumManager.h
    anticarium_pi/WeatherEmulator.h
    anticarium_pi/WeatherManager.h
    anticarium_pi/config/ApplicationSettings.h
    )

set(SOURCE_FILES
    anticarium_pi/AnticariumManager.cpp
    anticarium_pi/WeatherEmulator.cpp
    anticarium_pi/WeatherManager.cpp
    anticarium_pi/config/ApplicationSettings.cpp
    )

set(TARGET_NAME anticarium_pi_lib)

include(ExternLibs)

add_library(${TARGET_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/libs
)

target_link_libraries(${TARGET_NAME} PRIVATE anticarium_additional_libs)
ADDSHAREDTYPES(${TARGET_NAME})
ADDQT5CORE(${TARGET_NAME})
ADDJSON(${TARGET_NAME})
