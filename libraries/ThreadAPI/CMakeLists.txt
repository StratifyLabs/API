include(${CMAKE_CURRENT_LIST_DIR}/../API/api.cmake)
api2_target(
  NAME ThreadAPI
  TARGET TARGETS
  DEPENDENCIES FsAPI VarAPI ChronoAPI)

message(STATUS "ThreadAPI: Check to see if running linux and need to link to pthread and rt")
if(${CMSDK_IS_LINUX})
  message(STATUS "Running on Linux -- need to add pthread and rt dependencies")
  set(CONFIG_LIST release debug)
  foreach(TARGET ${TARGETS})
    message(STATUS "${ARGS_TARGET} -> pthread")
    message(STATUS "${ARGS_TARGET} -> rt")
    target_link_libraries(${TARGET} PUBLIC pthread rt)
  endforeach()
endif()