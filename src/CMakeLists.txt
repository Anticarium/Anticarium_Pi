set(HEADER_FILES
    TestClass.h
    )

set(SOURCE_FILES
    TestClass.cpp
    )

SET(TARGET_NAME anticarium_lib)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

project(${TARGET_NAME} VERSION 0.1 LANGUAGES CXX)
ADD_LIBRARY(${TARGET_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

find_package(Qt5Core)
target_link_libraries(${PROJECT_NAME} private Qt5::Core)
