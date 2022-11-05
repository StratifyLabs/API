macro(api_target NAME DEPENDENCIES)
  project(
    ${NAME}
    VERSION ${PROJECT_VERSION}
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
  if (IS_API AND API_PUBLIC_DEBUG_COMPILE_OPTIONS)
    target_compile_options(${DEBUG_TARGET} PUBLIC ${API_PUBLIC_DEBUG_COMPILE_OPTIONS})
  endif ()
  if (IS_API AND API_PUBLIC_COMPILE_OPTIONS)
    target_compile_options(${RELEASE_TARGET} PUBLIC ${API_PUBLIC_COMPILE_OPTIONS})
  endif ()
  if (IS_API AND API_PUBLIC_LINK_OPTIONS)
    target_link_options(${RELEASE_TARGET} PUBLIC ${API_PUBLIC_LINK_OPTIONS})
  endif ()
  cmsdk2_copy_target(
    SOURCE ${RELEASE_TARGET}
    DESTINATION ${DEBUG_TARGET})
  string(REPLACE ":" " " DEPENDENCY_LIST "${DEPENDENCIES}")
  cmsdk2_library_add_dependencies(
    TARGET ${RELEASE_TARGET}
    DEPENDENCIES ${DEPENDENCY_LIST}
    TARGETS RELEASE_TARGET_LIST)
  cmsdk2_library_add_dependencies(
    TARGET ${DEBUG_TARGET}
    TARGETS DEBUG_TARGET_LIST)
endmacro()

function(api2_target)
  cmsdk2_internal_parse_arguments(
    INTERNAL_FUNCTION_NAME api2_target
    ARGUMENTS ${ARGV}
    REQUIRED NAME
    ONE_VALUE NAME TARGETS VERSION
    MULTI_VALUE DEPENDENCIES PRECOMPILED_HEADERS)

  api_target(${ARGS_NAME} "${ARGS_DEPENDENCIES}")
  set(TARGET_LIST ${RELEASE_TARGET_LIST} ${DEBUG_TARGET_LIST})
  if (ARGS_TARGETS)
    set(${ARGS_TARGETS} ${TARGET_LIST} PARENT_SCOPE)
  endif ()
  foreach (TARGET ${TARGET_LIST})
    if (ARGS_PRECOMPILED_HEADERS AND FALSE)
      foreach (HEADER ${ARGS_PRECOMPILED_HEADERS})
        message(STATUS "  Adding precompiled header ${HEADER}")
        target_precompile_headers(${TARGET}
          PUBLIC
          $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${HEADER}>)
      endforeach ()
    endif ()
  endforeach ()

  set(${ARGS_NAME}_VERSION ${PROJECT_VERSION} CACHE INTERNAL "Set ${ARGS_NAME}_VERSION")
  message(STATUS "  Set ${ARGS_NAME}_VERSION -> ${PROJECT_VERSION}")
endfunction()

