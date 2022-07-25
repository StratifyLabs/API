cmake_minimum_required(VERSION 3.12)

include(${CMAKE_CURRENT_LIST_DIR}/../API/api.cmake)

api_target(VarAPI API)

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/magic_enum)
  set(MAGIC_ENUM_GIT_REPOSITORY "https://github.com/Neargye/magic_enum.git")
  set(MAGIC_ENUM_BRANCH "v0.8.0")
  execute_process(
    COMMAND git clone --branch ${MAGIC_ENUM_BRANCH} ${MAGIC_ENUM_GIT_REPOSITORY}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/magic_enum/include/magic_enum.hpp
  DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/var)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/magic_enum/include/magic_enum_fuse.hpp
  DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/var)