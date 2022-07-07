get_filename_component(SOS_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${SOS_NAME} CXX C)

# This will set the default RAM used by the application
set(RAM_SIZE 32768)

include(${CMAKE_CURRENT_SOURCE_DIR}/api.cmake)

set(DIRECTORIES
  FsAPI
  ChronoAPI
  VarAPI
  ThreadAPI
  SysAPI
  TestAPI
  PrinterAPI
  API
  )

api_test_executable(API "${DIRECTORIES}")


