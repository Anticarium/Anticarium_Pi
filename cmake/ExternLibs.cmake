function(ADDQT5CORE TARGET_NAME)
	find_package(Qt5 COMPONENTS Core REQUIRED)
	target_link_libraries(${TARGET_NAME} PRIVATE Qt5::Core)
endfunction()