include(${CMAKE_CURRENT_LIST_DIR}/../API/api.cmake)
api2_target(
  NAME ThreadAPI
  TARGETS TARGET_LIST
  DEPENDENCIES FsAPI VarAPI ChronoAPI)

message(STATUS "  ThreadAPI: Check to see if running linux and need to link to pthread and rt")
if(${CMSDK_IS_LINUX})
  foreach(TARGET ${TARGET_LIST})
    message(STATUS "${TARGET} -> pthread")
    message(STATUS "${TARGET} -> rt")
    target_link_libraries(${TARGET} PUBLIC pthread rt)
  endforeach()
endif()