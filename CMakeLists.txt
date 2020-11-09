cmake_minimum_required (VERSION 3.12)

if(NOT SOS_SDK_PATH)
	set(SOS_SDK_PATH $ENV{SOS_SDK_PATH})
endif()

set(CMAKE_MODULE_PATH ${SOS_SDK_PATH}/Tools/gcc/cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_MODULE_PATH}/sos-toolchain.cmake)

set(STRATIFYAPI_PROJECT_VERSION 4.0.0 CACHE INTERNAL "Stratify API version")
project(StratifyAPI
	LANGUAGES CXX C
	VERSION ${STRATIFYAPI_PROJECT_VERSION}
	)

include(sos-sdk)


include(StratifyOS)


include(CTest)

add_subdirectory(libraries/API API)
add_subdirectory(libraries/VarAPI VarAPI)
add_subdirectory(libraries/PrinterAPI PrinterAPI)
add_subdirectory(libraries/ChronoAPI ChronoAPI)
add_subdirectory(libraries/FsAPI FsAPI)
add_subdirectory(libraries/ThreadAPI ThreadAPI)
add_subdirectory(libraries/SysAPI SysAPI)
add_subdirectory(libraries/TestAPI TestAPI)

add_subdirectory(tests tests)
