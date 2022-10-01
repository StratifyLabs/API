project(ChronoAPI CXX C)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/API.cmake)
api2_add_test_executable(
  NAME ${PROJECT_NAME}
  RAM_SIZE 32768
  DEPENDENCIES FsAPI SysAPI TestAPI
)


