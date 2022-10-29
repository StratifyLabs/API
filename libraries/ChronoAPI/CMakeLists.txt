include(${CMAKE_CURRENT_LIST_DIR}/../API/api.cmake)

api2_target(
	NAME ChronoAPI
	DEPENDENCIES PrinterAPI)
