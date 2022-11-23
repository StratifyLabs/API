set(API_CONFIG_LIST release debug)

if (API_INCLUDE_TARGETS)
  if (CMSDK_IS_ARM)
    #cmsdk_include_target(StratifyOS_iface "${API_CONFIG_LIST}")
    cmsdk_include_target(StratifyOS_crt "${API_CONFIG_LIST}")
  endif ()
  cmsdk_include_target(API "${API_CONFIG_LIST}")
  cmsdk_include_target(VarAPI "${API_CONFIG_LIST}")
  cmsdk_include_target(PrinterAPI "${API_CONFIG_LIST}")
  cmsdk_include_target(SysAPI "${API_CONFIG_LIST}")
  cmsdk_include_target(ChronoAPI "${API_CONFIG_LIST}")
  cmsdk_include_target(FsAPI "${API_CONFIG_LIST}")
  cmsdk_include_target(ThreadAPI "${API_CONFIG_LIST}")
  cmsdk_include_target(TestAPI "${API_CONFIG_LIST}")
endif ()

macro(api_add_api_library_option NAME DEPENDENCIES LIB_OPTION)
  cmsdk2_add_library(
    NAME ${NAME}
    TARGET RELEASE_TARGET
    OPTION ${LIB_OPTION}
    CONFIG release
    ARCH ${CMSDK_ARCH})
  cmsdk2_add_sources(
    TARGET ${RELEASE_TARGET}
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
    BINARY_DIRECTORY ${RELEASE_TARGET}_src
    VISIBILITY PRIVATE)
  cmsdk2_add_sources(
    TARGET ${RELEASE_TARGET}
    DIRECTORY include
    BINARY_DIRECTORY ${RELEASE_TARGET}_include
    VISIBILITY PRIVATE)
  set_property(TARGET ${RELEASE_TARGET}
    PROPERTY
    CXX_STANDARD 17)
  set_property(TARGET ${RELEASE_TARGET}
    PROPERTY
    CXX_STANDARD_REQUIRED ON)
  set_property(TARGET ${RELEASE_TARGET}
    PROPERTY
    CXX_EXTENSIONS ON)
  target_sources(${RELEASE_TARGET}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/${NAME}.cmake)
  target_include_directories(${RELEASE_TARGET}
    PUBLIC
    $<INSTALL_INTERFACE:include/${NAME}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE)
  cmsdk2_add_library(
    NAME ${NAME}
    TARGET DEBUG_TARGET
    OPTION "${LIB_OPTION}"
    CONFIG debug
    ARCH ${CMSDK_ARCH})
  cmsdk2_library_add_dependencies(
    TARGET ${RELEASE_TARGET}
    DEPENDENCIES ${DEPENDENCIES}
    TARGETS RELEASE_TARGET_LIST)
  cmsdk2_copy_target(
    SOURCE ${RELEASE_TARGET}
    DESTINATION ${DEBUG_TARGET})
  set(TARGET_LIST ${RELEASE_TARGET_LIST} ${DEBUG_TARGET_LIST})
endmacro()

function(api2_add_library)
  cmsdk2_internal_parse_arguments(
    INTERNAL_FUNCTION_NAME api2_add_library
    ARGUMENTS ${ARGV}
    REQUIRED NAME
    ONE_VALUE NAME OPTION TARGETS VERSION
    MULTI_VALUE DEPENDENCIES PRECOMPILED_HEADERS)

  api_add_api_library_option(${ARGS_NAME} "${ARGS_DEPENDENCIES}" "${ARGS_OPTION}")
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
          $<INSTALL_INTERFACE:include/${HEADER}>
          $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${HEADER}>)
      endforeach ()
    endif ()
  endforeach ()

  if (ARGS_VERSION)
    set(${ARGS_NAME}_VERSION ${ARGS_VERSION} CACHE INTERNAL "Set ${ARGS_NAME}_VERSION")
  else ()
    set(${ARGS_NAME}_VERSION ${PROJECT_VERSION} CACHE INTERNAL "Set ${ARGS_NAME}_VERSION")
  endif ()
endfunction()

function(api_add_test_executable NAME RAM_SIZE DEPENDENCIES)
  cmsdk2_add_executable(
    NAME ${NAME}
    OPTION unittest
    CONFIG release
    ARCH ${CMSDK_ARCH}
    TARGET TEST_TARGET)
  set(MAIN_COMMON ${CMAKE_CURRENT_SOURCE_DIR}/../common/main.cpp)
  if (EXISTS ${MAIN_COMMON})
    set(MAIN_CPP ${MAIN_COMMON})
  else ()
    set(MAIN_CPP ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
  endif ()
  add_dependencies(API_test ${TEST_TARGET})
  target_sources(${TEST_TARGET}
    PRIVATE
    ${MAIN_CPP}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sl_config.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/UnitTest.hpp)
  target_include_directories(${TEST_TARGET}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src)
  set_property(TARGET ${TEST_TARGET} PROPERTY CXX_STANDARD 17)
  set(CTEST_OUTPUT_ON_FAILURE ON)
  cmsdk2_app_add_dependencies(
    TARGET ${TEST_TARGET}
    RAM_SIZE ${RAM_SIZE}
    DEPENDENCIES ${DEPENDENCIES})
  target_compile_options(${TEST_TARGET}
    PRIVATE
    -Os)
  if (${CMSDK_IS_LINK})
    cmsdk2_add_test(TARGET ${TEST_TARGET})
  endif ()
endfunction()

function(api2_add_test_executable)
  set(OPTIONS "")
  set(PREFIX ARGS)
  set(ONE_VALUE_ARGS NAME RAM_SIZE)
  set(MULTI_VALUE_ARGS DEPENDENCIES)
  cmake_parse_arguments(PARSE_ARGV 0 ${PREFIX} "${OPTIONS}" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}")
  set(REQUIRED_ARGS NAME DEPENDENCIES)
  foreach (VALUE ${REQUIRED_ARGS})
    if (NOT ARGS_${VALUE})
      message(FATAL_ERROR "api2_add_test_executable requires ${VALUE}")
    endif ()
  endforeach ()
  api_add_test_executable(${ARGS_NAME} ${ARGS_RAM_SIZE} "${ARGS_DEPENDENCIES}")
endfunction()
