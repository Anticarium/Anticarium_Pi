set(HEADER_FILES
    config/ApplicationSettings.h
    config/DynamicSettings.h
    config/PIDValues.h
)

set(SOURCE_FILES
    config/ApplicationSettings.cpp
    config/DynamicSettings.cpp
    config/PIDValues.cpp
)

set(TARGET_NAME anticarium_config_lib)

include(ExternLibs)

add_library(${TARGET_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/config
)

ADDQT5CORE(${TARGET_NAME})
ADDSPDLOG(${TARGET_NAME})
