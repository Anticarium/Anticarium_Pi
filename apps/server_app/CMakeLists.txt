set(TARGET_NAME anticarium_pi_server_app)

include(ExternLibs)

add_executable(${TARGET_NAME}
    main.cpp
)

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${TARGET_NAME} PRIVATE anticarium_pi_lib)

ADDQT5CORE(${TARGET_NAME})
ADDSHAREDTYPES(${TARGET_NAME})
