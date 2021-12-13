include(ExternLibs)
include(GoogleTest)

set(TARGET_NAME anticarium_pi_tests)
set(TEST_DATA_DIR_HEADER_PATH ${CMAKE_BINARY_DIR}/tests/include/shared_types_tests)

set(HEADER_FILES
    anticarium_pi_tests/TestsUtility.h
)

set(SOURCE_FILES
    main.cpp
    anticarium_pi_tests/TestsUtility.cpp
    WeatherEmulatorTests.cpp
    config/ApplicationSettingsTests.cpp
)

add_executable(${TARGET_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

configure_file(TestDataDirectory.h.in  ${TEST_DATA_DIR_HEADER_PATH}/TestDataDirectory.h)

target_include_directories(${TARGET_NAME} PRIVATE
    ${TEST_DATA_DIR_HEADER_PATH}
    ${CMAKE_SOURCE_DIR}/src/anticarium_pi
    ${CMAKE_SOURCE_DIR}/src/anticarium_camera
    ${CMAKE_SOURCE_DIR}/src/config
    ${CMAKE_SOURCE_DIR}/libs/pid
)
target_link_libraries(${TARGET_NAME} PRIVATE
    anticarium_pi_lib
    anticarium_camera_lib
    anticarium_config_lib
)

ADDJSON(${TARGET_NAME})
ADDGTEST(${TARGET_NAME})
ADDQT5CORE(${TARGET_NAME})
ADDQT5NETWORK(${TARGET_NAME})
ADDSHAREDTYPES(${TARGET_NAME})
