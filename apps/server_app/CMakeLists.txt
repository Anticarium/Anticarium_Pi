set(TARGET_NAME anticarium_pi_server_app)

include(ExternLibs)

add_executable(${TARGET_NAME}
    main.cpp
)

configure_file(${CMAKE_SOURCE_DIR}/settings.ini.in settings.ini)

target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/anticarium_pi
    ${CMAKE_SOURCE_DIR}/src/config
    ${CMAKE_SOURCE_DIR}/libs/pid
)

target_link_libraries(${TARGET_NAME} PRIVATE
    anticarium_pi_lib
    anticarium_config_lib
)

ADDQT5CORE(${TARGET_NAME})
ADDSHAREDTYPES(${TARGET_NAME})
ADDSPDLOG(${TARGET_NAME})
ADDQT5NETWORK(${TARGET_NAME})
