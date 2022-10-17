macro(api_target NAME DEPENDENCIES)
  project(
    ${NAME}
    VERSION ${API_PROJECT_VERSION}
    LANGUAGES CXX)
  install(DIRECTORY include/ DESTINATION include/${NAME})
  cmsdk2_add_library(
    TARGET RELEASE_TARGET
    NAME ${NAME}
    CONFIG release
    ARCH ${CMSDK_ARCH})
  set_property(TARGET ${RELEASE_TARGET}
    PROPERTY
    CXX_STANDARD 17)
  set_property(TARGET ${RELEASE_TARGET}
    PROPERTY
    CXX_STANDARD_REQUIRED ON)
  set_property(TARGET ${RELEASE_TARGET}
    PROPERTY
    CXX_EXTENSIONS ON)
  cmsdk2_add_sources(
    TARGET ${RELEASE_TARGET}
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
    VISIBILITY PRIVATE)
  cmsdk2_add_sources(
    TARGET ${RELEASE_TARGET}
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
    VISIBILITY PRIVATE)
  target_sources(${RELEASE_TARGET}
    PRIVATE
    ${HEADERS}
    ${SOURCES})
  target_compile_definitions(${RELEASE_TARGET}
    PRIVATE
    __PROJECT_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    __PROJECT_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    __PROJECT_VERSION_PATCH=${PROJECT_VERSION_PATCH})
  if(CMSDK_IS_ARM)
    target_compile_options(${RELEASE_TARGET}
      PUBLIC
      -fno-threadsafe-statics)
  endif()
  target_include_directories(${RELEASE_TARGET}
    PUBLIC
    $<INSTALL_INTERFACE:include/${NAME}>
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
  target_include_directories(${RELEASE_TARGET}
    PUBLIC
    $<INSTALL_INTERFACE:include/${NAME}>
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
  cmsdk2_add_library(
    TARGET DEBUG_TARGET
    NAME ${NAME}
    CONFIG debug
    ARCH ${CMSDK_ARCH})
  string(COMPARE EQUAL ${NAME} API IS_API)
  if(IS_API AND API_PUBLIC_DEBUG_COMPILE_OPTIONS)
    target_compile_options(${DEBUG_TARGET} PUBLIC ${API_PUBLIC_DEBUG_COMPILE_OPTIONS})
  endif()
  if(IS_API AND API_PUBLIC_COMPILE_OPTIONS)
    target_compile_options(${RELEASE_TARGET} PUBLIC ${API_PUBLIC_COMPILE_OPTIONS})
  endif()
  if(IS_API AND API_PUBLIC_LINK_OPTIONS)
    target_link_options(${RELEASE_TARGET} PUBLIC ${API_PUBLIC_LINK_OPTIONS})
  endif()
  cmsdk2_copy_target(
    SOURCE ${RELEASE_TARGET}
    DESTINATION ${DEBUG_TARGET})
  string(REPLACE ":" " " DEPENDENCY_LIST "${DEPENDENCIES}")
  cmsdk2_library_add_dependencies(
    TARGET ${RELEASE_TARGET}
    DEPENDENCIES ${DEPENDENCY_LIST})
  cmsdk2_library_add_dependencies(
    TARGET ${DEBUG_TARGET}
    DEPENDENCIES ${DEPENDENCY_LIST})
endmacro()

function(api2_target)
  set(OPTIONS "")
  set(PREFIX ARGS)
  set(ONE_VALUE_ARGS NAME TARGETS)
  set(MULTI_VALUE_ARGS DEPENDENCIES)
  cmake_parse_arguments(PARSE_ARGV 0 ${PREFIX} "${OPTIONS}" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}")
  set(REQUIRED_ARGS NAME)
  foreach(VALUE ${REQUIRED_ARGS})
    if(NOT ARGS_${VALUE})
      message(FATAL_ERROR "api2_target requires ${VALUE}")
    endif()
  endforeach()
  api_target(${ARGS_NAME} "${ARGS_DEPENDENCIES}")
  if(ARGS_TARGETS)
    set(${ARGS_TARGETS} ${RELEASE_TARGET} ${DEBUG_TARGET} PARENT_SCOPE)
  endif()
endfunction()

