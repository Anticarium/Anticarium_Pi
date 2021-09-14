set(TARGET_NAME anticarium_pi_server_app)

include(ExternLibs)

add_executable(${TARGET_NAME}
    main.cpp
)

ADDQT5CORE(${TARGET_NAME})
