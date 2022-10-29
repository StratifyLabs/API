include(${CMAKE_CURRENT_LIST_DIR}/../API/api.cmake)

api2_target(
  NAME SysAPI
  DEPENDENCIES ThreadAPI FsAPI PrinterAPI VarAPI)

