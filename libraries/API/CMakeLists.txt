include(${CMAKE_CURRENT_LIST_DIR}/api.cmake)
api2_target(
  NAME API
  TARGETS TARGETS)
foreach(TARGET ${TARGETS})
  message(STATUS "API has target ${TARGET}")
  target_sources(${TARGET}
    PRIVATE
    api.cmake
    ../API.cmake)
  if(API_PUBLIC_COMPILE_OPTIONS)
    message(STATUS "Apply: ${API_PUBLIC_COMPILE_OPTIONS} to ${TARGET} as PUBLIC")
    target_compile_options(${TARGET} PUBLIC ${API_PUBLIC_COMPILE_OPTIONS})
  endif()
  if(${CMSDK_IS_ARM})
    get_target_property(LINK_LIBS ${TARGET} INTERFACE_LINK_LIBRARIES)
    get_target_property(CONFIG ${TARGET} CMSDK_PROPERTY_CONFIG)
    get_target_property(ARCH ${TARGET} CMSDK_PROPERTY_ARCH)
    target_compile_options(${TARGET} PUBLIC -mlong-calls)
    target_link_libraries(${TARGET} PUBLIC StratifyOS_crt_${CONFIG}_${ARCH} stdc++ supc++)
    message(STATUS "API_${CONFIG}_${ARCH} -> crt stdc++ supc++")
  endif()
endforeach()
install(FILES
  ../API.cmake
  DESTINATION ${CMSDK_LOCAL_PATH}/cmake/targets)
