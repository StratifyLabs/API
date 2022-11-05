include(${CMAKE_CURRENT_LIST_DIR}/../API/api.cmake)

api2_target(
  NAME FsAPI
  PRECOMPILED_HEADERS fs/File.hpp fs/FileSystem.hpp fs/DataFile.hpp fs/ViewFile.hpp
  DEPENDENCIES ChronoAPI PrinterAPI)
