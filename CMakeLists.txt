cmake_minimum_required (VERSION 3.12)
cmsdk2_minimum_required(2.1.4)
project(API
	LANGUAGES CXX C
	VERSION 1.7.0)
add_subdirectory(libraries/API API)
add_subdirectory(libraries/VarAPI VarAPI)
add_subdirectory(libraries/PrinterAPI PrinterAPI)
add_subdirectory(libraries/ChronoAPI ChronoAPI)
add_subdirectory(libraries/FsAPI FsAPI)
add_subdirectory(libraries/ThreadAPI ThreadAPI)
add_subdirectory(libraries/SysAPI SysAPI)
add_subdirectory(libraries/TestAPI TestAPI)
option(API_IS_TEST "Enable test builds for API" OFF)
# Always available so dependency libs can use it
add_custom_target(API_test ALL)
if(API_IS_TEST)
	include(CTest)
	add_subdirectory(tests tests)
endif()

