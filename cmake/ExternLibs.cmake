function(ADDSPDLOG TARGET_NAME)
    find_package(spdlog CONFIG REQUIRED)
    target_link_libraries(${TARGET_NAME} PRIVATE spdlog::spdlog)
endfunction()

function(ADDQT5CORE TARGET_NAME)
	find_package(Qt5 COMPONENTS Core REQUIRED)
	target_link_libraries(${TARGET_NAME} PRIVATE Qt5::Core)
endfunction()

function(ADDQT5NETWORK TARGET_NAME)
        find_package(Qt5 COMPONENTS Network REQUIRED)
        target_link_libraries(${TARGET_NAME} PRIVATE Qt5::Network)
endfunction()

function(ADDJSON TARGET_NAME)
        find_package(nlohmann_json CONFIG REQUIRED)
        target_link_libraries(${TARGET_NAME} PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
endfunction()

function(ADDRASPICAM TARGET_NAME)
    find_package(raspicam CONFIG REQUIRED)
    target_link_libraries(${TARGET_NAME} PRIVATE raspicam)
endfunction()

function(FETCHSHAREDTYPES)
	include(FetchContent)
	FetchContent_Declare(
	  shared_types
	  GIT_REPOSITORY https://github.com/Anticarium/Shared_Types.git
          GIT_TAG        v1.3.0
	)

	FetchContent_GetProperties(shared_types)
	if(NOT shared_types_POPULATED)
	  FetchContent_Populate(shared_types)
	endif()
	ADD_SUBDIRECTORY(${shared_types_SOURCE_DIR} ${shared_types_BINARY_DIR} EXCLUDE_FROM_ALL)
endfunction()

function(ADDSHAREDTYPES TARGET_NAME)
	TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME}
			PRIVATE
			$<BUILD_INTERFACE:${shared_types_SOURCE_DIR}/src>
			$<BUILD_INTERFACE:${shared_types_SOURCE_DIR}/include>
			$<BUILD_INTERFACE:${shared_types_BINARY_DIR}>
			$<INSTALL_INTERFACE:include>)

	TARGET_LINK_LIBRARIES(${TARGET_NAME} PUBLIC shared_types_include shared_types_lib)
endfunction()

function(ADDGTEST TARGET_NAME)
        include(FetchContent)
        FetchContent_Declare(
                googletest
                URL https://github.com/google/googletest/archive/2f80c2ba71c0e8922a03b9b855e5b019ad1f7064.zip
        )
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        target_link_libraries(${TARGET_NAME} PRIVATE gtest_main)
        FetchContent_MakeAvailable(googletest)
endfunction()
