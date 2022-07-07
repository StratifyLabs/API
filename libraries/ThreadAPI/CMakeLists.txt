cmake_minimum_required(VERSION 3.12)

include(${CMAKE_CURRENT_LIST_DIR}/../API/api.cmake)

set(DIRECTORIES
  FsAPI
  VarAPI
  ChronoAPI
  )

api_target(ThreadAPI "${DIRECTORIES}")

message(STATUS "Check to see if running linux and need to link to pthread and rt")
if(SOS_IS_LINUX)
  message(STATUS "Running on Linux -- need to add pthread and rt dependencies")
  set(CONFIG_LIST release debug)
  foreach(CONFIG ${CONFIG_LIST})
    set(TARGET ThreadAPI_${CONFIG}_link)
    message(STATUS "Adding pthread and rt to ${TARGET}")
    target_link_libraries(ThreadAPI_${CONFIG}_link PUBLIC pthread rt)
  endforeach()
endif()