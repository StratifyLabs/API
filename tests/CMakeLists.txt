cmake_minimum_required (VERSION 3.12)

if(NOT SOS_SDK_PATH)
	set(SOS_SDK_PATH $ENV{SOS_SDK_PATH})
endif()

set(CMAKE_MODULE_PATH ${SOS_SDK_PATH}/Tools/gcc/cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_MODULE_PATH}/sos-toolchain.cmake)
include(sos-sdk)

add_subdirectory(API testsAPI)
add_subdirectory(ChronoAPI testsChronoAPI)
add_subdirectory(FsAPI testsFsAPI)
add_subdirectory(VarAPI testsVarAPI)
add_subdirectory(ThreadAPI testsThreadAPI)


add_custom_target(coverage
	DEPENDS coverage_test
	coverage_ThreadAPI_coverage_link
	coverage_FsAPI_coverage_link
	coverage_ChronoAPI_coverage_link
	coverage_VarAPI_coverage_link
	)

add_custom_target(coverage_test
	COMMAND ctest -VV
	DEPENDS clean_coverage
	)

add_custom_target(clean_coverage
	DEPENDS
	clean_coverage_ThreadAPI_coverage_link
	clean_coverage_FsAPI_coverage_link
	clean_coverage_ChronoAPI_coverage_link
	clean_coverage_VarAPI_coverage_link
	)


