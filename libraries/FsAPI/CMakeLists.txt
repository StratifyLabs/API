cmake_minimum_required (VERSION 3.10)

include(${CMAKE_CURRENT_LIST_DIR}/../API/api.cmake)

set(DIRECTORIES
	SysAPI
	ChronoAPI
	PrinterAPI
	)

api_target(FsAPI "${DIRECTORIES}")
