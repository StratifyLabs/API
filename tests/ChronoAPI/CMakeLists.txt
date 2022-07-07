
get_filename_component(SOS_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${SOS_NAME} CXX C)

# This will set the default RAM used by the application
set(RAM_SIZE 32768)

include(${CMAKE_CURRENT_SOURCE_DIR}/../API/api.cmake)

set(DIRECTORIES
  FsAPI
  SysAPI
  TestAPI
  )

api_test_executable(ChronoAPI "${DIRECTORIES}")


