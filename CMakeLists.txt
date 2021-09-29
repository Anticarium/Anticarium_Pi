cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(TARGET_NAME anticarium_pi)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include(ExternLibs)
include(HunterGate)
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.297.tar.gz"
    SHA1 "3319fe6a3b08090df7df98dee75134d68e2ef5a3"
)

file(READ VERSION CURRENT_VERSION)
project(${TARGET_NAME} VERSION ${CURRENT_VERSION})
message(STATUS "Adding ${TARGET_NAME} v${CURRENT_VERSION}")
configure_file(VersionConfig.h.in ${TARGET_NAME}_VersionConfig.h)

hunter_add_package(nlohmann_json)
find_package(Qt5 COMPONENTS Core)

FETCHSHAREDTYPES()

add_subdirectory(apps/server_app)
add_subdirectory(src)
add_subdirectory(libs)

if(ADD_${TARGET_NAME}_TESTS)
    add_subdirectory(tests)
endif()


