cmake_minimum_required (VERSION 3.12)


include(${CMAKE_CURRENT_LIST_DIR}/../API/api.cmake)

set(DIRECTORIES
	VarAPI
	)


api_target(PrinterAPI "${DIRECTORIES}" 4.0.0)
