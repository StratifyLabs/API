
include(${CMAKE_CURRENT_LIST_DIR}/api.cmake)

api_target(API "")

target_sources(${RELEASE_TARGET}
	PRIVATE
	api.cmake
	StratifyAPI.cmake
	)

install(FILES
	StratifyAPI.cmake
	DESTINATION
	cmake/targets)
