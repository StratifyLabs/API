
include(${CMAKE_CURRENT_LIST_DIR}/api.cmake)

api_target(API "")

target_sources(${RELEASE_TARGET}
  PRIVATE
  api.cmake
  ../API.cmake
  )

install(FILES
  ../API.cmake
  DESTINATION ${CMSDK_PATH}/cmake/targets)
