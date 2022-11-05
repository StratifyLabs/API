include(${CMAKE_CURRENT_LIST_DIR}/../API/api.cmake)

api2_target(
	NAME ChronoAPI
	PRECOMPILED_HEADERS chrono/MicroTime.hpp chrono/ClockTimer.hpp chrono/DateTime.hpp
	DEPENDENCIES PrinterAPI)
