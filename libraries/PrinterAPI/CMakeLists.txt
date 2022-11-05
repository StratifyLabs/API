include(${CMAKE_CURRENT_LIST_DIR}/../API/api.cmake)

api2_target(
	NAME PrinterAPI
	PRECOMPILED_HEADERS printer/Printer.hpp
	DEPENDENCIES VarAPI)
