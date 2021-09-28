set(HEADER_FILES
    anticarium_pi/TestClass.h
    )

set(SOURCE_FILES
    anticarium_pi/TestClass.cpp
    )

set(TARGET_NAME anticarium_lib)

include(ExternLibs)


add_library(${TARGET_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

ADDSHAREDTYPES(${TARGET_NAME})
ADDQT5CORE(${TARGET_NAME})
