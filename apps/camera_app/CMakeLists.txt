set(TARGET_NAME anticarium_pi_camera_app)

include(ExternLibs)

add_executable(${TARGET_NAME}
    main.cpp
)

configure_file(${CMAKE_SOURCE_DIR}/settings.ini.in settings.ini)

target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/anticarium_camera
    ${CMAKE_SOURCE_DIR}/src/config
    ${CMAKE_SOURCE_DIR}/libs/raspicam
)

target_link_libraries(${TARGET_NAME} PRIVATE
    anticarium_camera_lib
    anticarium_config_lib
    raspicam
)

ADDQT5CORE(${TARGET_NAME})
ADDSPDLOG(${TARGET_NAME})
ADDQT5NETWORK(${TARGET_NAME})
