cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(TARGET_NAME anticarium_pi)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include(ExternLibs)

file(READ VERSION CURRENT_VERSION)
project(${TARGET_NAME} VERSION ${CURRENT_VERSION})
message(STATUS "Adding ${TARGET_NAME} v${CURRENT_VERSION}")
configure_file(VersionConfig.h.in ${TARGET_NAME}_VersionConfig.h)

include(${CMAKE_CURRENT_SOURCE_DIR}/conan/conanbuildinfo.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/conan/conan_paths.cmake)
conan_basic_setup()

FETCHSHAREDTYPES()

add_subdirectory(apps/server_app)

