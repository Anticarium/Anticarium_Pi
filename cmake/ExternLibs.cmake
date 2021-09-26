function(ADDQT5CORE TARGET_NAME)
	find_package(Qt5 COMPONENTS Core REQUIRED)
	target_link_libraries(${TARGET_NAME} PRIVATE Qt5::Core)
endfunction()


function(ADDJSON TARGET_NAME)
        find_package(nlohmann_json CONFIG REQUIRED)
        target_link_libraries(${TARGET_NAME} PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
endfunction()

function(FETCHSHAREDTYPES)
	include(FetchContent)
	FetchContent_Declare(
	  shared_types
	  GIT_REPOSITORY https://github.com/Anticarium/Shared_Types.git
	  GIT_TAG        v1.1.3
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
