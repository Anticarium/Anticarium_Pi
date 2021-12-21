set(HEADER_FILES
    anticarium_camera/StreamManager.h
    anticarium_camera/UDPSender.h
    anticarium_camera/UDPListener.h
    anticarium_camera/Camera.h
    anticarium_camera/ImageProcess.h
    anticarium_camera/PiImage.hpp
    anticarium_camera/Client.hpp
    anticarium_camera/UDPSwitch.h
)

set(SOURCE_FILES
    anticarium_camera/StreamManager.cpp
    anticarium_camera/UDPSender.cpp
    anticarium_camera/UDPListener.cpp
    anticarium_camera/Camera.cpp
    anticarium_camera/ImageProcess.cpp
    anticarium_camera/UDPSwitch.cpp
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
    raspicam
)

ADDQT5CORE(${TARGET_NAME})
ADDSPDLOG(${TARGET_NAME})
ADDQT5NETWORK(${TARGET_NAME})
