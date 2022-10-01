

macro(api_target NAME DEPENDENCIES)
  project(
    ${NAME}
    VERSION ${API_PROJECT_VERSION}
    LANGUAGES CXX)

  install(DIRECTORY include/ DESTINATION include/${NAME})

  cmsdk2_add_sources(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
    LIST SOURCES)

  cmsdk2_add_sources(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIST HEADERS)

  cmsdk2_add_library(
    TARGET RELEASE_TARGET
    NAME ${NAME}
    CONFIG release
    ARCH ${CMSDK_ARCH}
  )

  set_property(TARGET ${RELEASE_TARGET}
    PROPERTY
    CXX_STANDARD 17
    )

  set_property(TARGET ${RELEASE_TARGET}
    PROPERTY
    CXX_STANDARD_REQUIRED ON
    )

  set_property(TARGET ${RELEASE_TARGET}
    PROPERTY
    CXX_EXTENSIONS ON
    )

  target_sources(${RELEASE_TARGET}
    PRIVATE
    ${HEADERS}
    ${SOURCES}
    )

  target_compile_definitions(${RELEASE_TARGET}
    PRIVATE
    __PROJECT_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    __PROJECT_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    __PROJECT_VERSION_PATCH=${PROJECT_VERSION_PATCH}
    )

  target_compile_options(${RELEASE_TARGET}
    PRIVATE
    -Os
    )

  if(CMSDK_IS_ARM)
    target_compile_options(${RELEASE_TARGET}
      PUBLIC
      -fno-threadsafe-statics
      )
  endif()

  target_include_directories(${RELEASE_TARGET}
    PUBLIC
    $<INSTALL_INTERFACE:include/${NAME}>
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )

  string(COMPARE EQUAL ${NAME} API IS_API)
  if(IS_API AND CMSDK_IS_ARM)
    target_compile_options(${RELEASE_TARGET}
      INTERFACE
      -mlong-calls)
  endif()

  target_include_directories(${RELEASE_TARGET}
    PUBLIC
    $<INSTALL_INTERFACE:include/${NAME}>
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )

  cmsdk2_add_library(
    TARGET DEBUG_TARGET
    NAME ${NAME}
    CONFIG debug
    ARCH ${CMSDK_ARCH}
  )

  cmsdk2_copy_target(
    SOURCE ${RELEASE_TARGET}
    DESTINATION ${DEBUG_TARGET}
  )

  string(REPLACE ":" " " DEPENDENCY_LIST "${DEPENDENCIES}")
  cmsdk2_library_add_targets_for_architectures(
    TARGET ${RELEASE_TARGET}
    DEPENDENCIES ${DEPENDENCY_LIST}
  )
  cmsdk2_library_add_targets_for_architectures(
    TARGET ${DEBUG_TARGET}
    DEPENDENCIES ${DEPENDENCY_LIST}
  )

  if(IS_API)
    get_target_property(RELEASE_LINK_LIBS ${RELEASE_TARGET} INTERFACE_LINK_LIBRARIES)
    get_target_property(DEBUG_LINK_LIBS ${DEBUG_TARGET} INTERFACE_LINK_LIBRARIES)
    if(CMSDK_IS_ARM)
      target_link_libraries(API_release_${CMSDK_ARCH} PUBLIC StratifyOS_crt_release_${CMSDK_ARCH} stdc++ supc++)
      target_link_libraries(API_debug_${CMSDK_ARCH} PUBLIC StratifyOS_crt_debug_${CMSDK_ARCH} stdc++ supc++)
      message(STATUS "API_release_${CMSDK_ARCH} -> crt stdc++ supc++")
      message(STATUS "API_debug_${CMSDK_ARCH} -> crt stdc++ supc++")
      foreach(ARCH ${CMSDK_ARCH_LIST})
        target_link_libraries(API_release_${ARCH} PUBLIC StratifyOS_crt_release_${ARCH} stdc++ supc++)
        target_link_libraries(API_debug_${ARCH} PUBLIC StratifyOS_crt_debug_${ARCH} stdc++ supc++)
        message(STATUS "API_release_${ARCH} -> crt stdc++ supc++")
        message(STATUS "API_debug_${ARCH} -> crt stdc++ supc++")
      endforeach()
    endif()
  endif()
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

