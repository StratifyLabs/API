cmake_minimum_required (VERSION 3.10)


include(${CMAKE_CURRENT_LIST_DIR}/../API/api.cmake)
set(DIRECTORIES
	PrinterAPI
	)

api_target(ChronoAPI "${DIRECTORIES}")
