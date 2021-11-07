cmake_minimum_required(VERSION 3.12)


include(${CMAKE_CURRENT_LIST_DIR}/../API/api.cmake)

set(DIRECTORIES
  FsAPI
  PrinterAPI
  VarAPI
  )

api_target(SysAPI "${DIRECTORIES}")

