
include(${CMAKE_CURRENT_LIST_DIR}/api.cmake)

if(SOS_IS_ARM)
	set(DIRECTORIES StratifyOS_iface)
else()
	set(DIRECTORIES "")
endif()

api_target(API "${DIRECTORIES}")

target_sources(${RELEASE_TARGET}
	PRIVATE
	api.cmake
	../API.cmake
	)

install(FILES
	../API.cmake
	DESTINATION
	cmake/targets)
