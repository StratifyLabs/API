#Copy this file to the application project folder as CMakeLists.txt
cmake_minimum_required (VERSION 3.12)

if(NOT SOS_SDK_PATH)
	set(SOS_SDK_PATH $ENV{SOS_SDK_PATH})
endif()

set(CMAKE_MODULE_PATH ${SOS_SDK_PATH}/Tools/gcc/cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_MODULE_PATH}/sos-toolchain.cmake)
include(sos-sdk)

get_filename_component(SOS_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${SOS_NAME} CXX C)

# This will set the default RAM used by the application
set(RAM_SIZE 32768)

include(${CMAKE_CURRENT_SOURCE_DIR}/../API/api.cmake)

set(DIRECTORIES
	FsAPI
	SysAPI
	TestAPI
	)

api_test_executable(ChronoAPI "${DIRECTORIES}")


