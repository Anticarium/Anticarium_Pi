set(HEADER_FILES
    pid/PID.h
)

set(SOURCE_FILES
    pid/PID.cpp
)

set(TARGET_NAME anticarium_additional_libs)

add_library(${TARGET_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
