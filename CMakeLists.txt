cmake_minimum_required (VERSION 3.12)

if(NOT SOS_SDK_PATH)
	set(SOS_SDK_PATH $ENV{SOS_SDK_PATH})
endif()

set(CMAKE_MODULE_PATH ${SOS_SDK_PATH}/cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_MODULE_PATH}/sos-toolchain.cmake)

set(API_PROJECT_VERSION 1.1.0 CACHE INTERNAL "API version")
project(API
	LANGUAGES CXX C
	VERSION ${API_PROJECT_VERSION}
	)

include(sos-sdk)


if(SOS_IS_ARM AND NOT DEFINED API_IS_SDK)
	include(StratifyOS)
endif()

include(CTest)

add_subdirectory(libraries/API API)
add_subdirectory(libraries/VarAPI VarAPI)
add_subdirectory(libraries/PrinterAPI PrinterAPI)
add_subdirectory(libraries/ChronoAPI ChronoAPI)
add_subdirectory(libraries/FsAPI FsAPI)
add_subdirectory(libraries/ThreadAPI ThreadAPI)
add_subdirectory(libraries/SysAPI SysAPI)
add_subdirectory(libraries/TestAPI TestAPI)

option(API_IS_TEST OFF "Enable test builds")

if(API_IS_TEST)
	add_subdirectory(tests tests)
endif()

