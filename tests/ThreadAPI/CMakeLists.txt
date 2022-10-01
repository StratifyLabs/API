project(ThreadAPI CXX C)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/API.cmake)
api2_add_test_executable(
  NAME ${PROJECT_NAME}
  RAM_SIZE 65536
  DEPENDENCIES ThreadAPI TestAPI)



