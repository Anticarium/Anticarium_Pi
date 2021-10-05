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
    config/ApplicationSettingsTests.cpp
    WeatherEmulatorTests.cpp
)

add_executable(${TARGET_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

configure_file(TestDataDirectory.h.in  ${TEST_DATA_DIR_HEADER_PATH}/TestDataDirectory.h)

target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${TEST_DATA_DIR_HEADER_PATH}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/libs
)
target_link_libraries(${TARGET_NAME} PRIVATE anticarium_pi_lib)

ADDJSON(${TARGET_NAME})
ADDGTEST(${TARGET_NAME})
ADDQT5CORE(${TARGET_NAME})
ADDSHAREDTYPES(${TARGET_NAME})
