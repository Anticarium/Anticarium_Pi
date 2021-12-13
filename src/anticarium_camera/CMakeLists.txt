set(HEADER_FILES
    anticarium_camera/AnticariumCameraManager.h
)

set(SOURCE_FILES
    anticarium_camera/AnticariumCameraManager.cpp
)

set(TARGET_NAME anticarium_camera_lib)

include(ExternLibs)

add_library(${TARGET_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/anticarium_camera
    ${CMAKE_SOURCE_DIR}/src/config
    ${CMAKE_SOURCE_DIR}/libs/raspicam
)

target_link_libraries(${TARGET_NAME} PRIVATE
    anticarium_config_lib
)

ADDQT5CORE(${TARGET_NAME})
ADDSPDLOG(${TARGET_NAME})
ADDQT5NETWORK(${TARGET_NAME})
