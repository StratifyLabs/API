include(${CMAKE_CURRENT_LIST_DIR}/api.cmake)

api2_target(
  NAME API
  TARGETS TARGETS
)

foreach(TARGET ${TARGETS})
  target_sources(${TARGET}
    PRIVATE
    api.cmake
    ../API.cmake
    )
endforeach()

install(FILES
  ../API.cmake
  DESTINATION ${CMSDK_LOCAL_PATH}/cmake/targets)
