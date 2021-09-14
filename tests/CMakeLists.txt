cmake_minimum_required(VERSION 3.14)
project(anticarium_test)
set(TARGET_EXE anticarium_test)
# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

set(HEADER_FILES
  io_tests/IoTest.h
  dht11_tests/Dht11Test.h
  )

set(SOURCE_FILES
    io_tests/IoTest.cpp
    io_tests/PwmTest.cpp
    dht11_tests/Dht11Test.cpp
    )


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/53495a2a7d6ba7e0691a7f3602e9a5324bba6e45.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  ${TARGET_EXE}
  ${HEADER_FILES}
  ${SOURCE_FILES}
)

find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
target_link_libraries(${TARGET_EXE} ${WIRINGPI_LIBRARIES})

include_directories(${anticarium_lib_INCLUDE_DIRS})
target_link_libraries(${TARGET_EXE} anticarium_lib)

target_link_libraries(
  ${TARGET_EXE}
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TARGET_EXE})
