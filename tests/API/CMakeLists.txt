get_filename_component(DIRECTORY_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${DIRECTORY_NAME} CXX C)

# This will set the default RAM used by the application
include(${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/API.cmake)

api2_add_test_executable(
  NAME API
  DEPENDENCIES TestAPI
  RAM_SIZE 32768
)


