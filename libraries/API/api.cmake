

macro(api_target NAME DIRECTORIES)

  project(
    ${NAME}
    VERSION ${API_PROJECT_VERSION}
    LANGUAGES CXX)

  install(DIRECTORY include/ DESTINATION include/${NAME})

  cmsdk_add_subdirectory(PRIVATE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src)
  cmsdk_add_subdirectory(PUBLIC_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/include)
  set(FORMAT_LIST ${PRIVATE_SOURCES} ${PUBLIC_SOURCES})

  cmsdk_library_target(RELEASE ${NAME} "" release ${CMSDK_ARCH})
  add_library(${RELEASE_TARGET} STATIC)

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
    ${PUBLIC_SOURCES}
    ${PRIVATE_SOURCES}
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
    INTERFACE
    $<INSTALL_INTERFACE:include/${NAME}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
    )

  foreach(DIRECTORY ${DIRECTORIES})
    target_include_directories(${RELEASE_TARGET}
      INTERFACE
      $<INSTALL_INTERFACE:include/${DIRECTORY}>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../${DIRECTORY}/include>
      )
  endforeach(DIRECTORY)

  string(COMPARE EQUAL ${NAME} API IS_API)
  set(LOCAL_DIRECTORIES ${DIRECTORIES})
  if(IS_API AND CMSDK_IS_ARM)
    #list(APPEND LOCAL_DIRECTORIES StratifyOS_crt)
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

  cmsdk_library_target(DEBUG ${NAME} "" debug ${CMSDK_ARCH})
  add_library(${DEBUG_TARGET} STATIC)
  cmsdk_copy_target(${RELEASE_TARGET} ${DEBUG_TARGET})

  cmsdk_library_add_arch_targets("${RELEASE_OPTIONS}" ${CMSDK_ARCH} "${LOCAL_DIRECTORIES}")
  cmsdk_library_add_arch_targets("${DEBUG_OPTIONS}" ${CMSDK_ARCH} "${LOCAL_DIRECTORIES}")

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

