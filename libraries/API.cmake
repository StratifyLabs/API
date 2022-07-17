set(API_CONFIG_LIST release debug)

if(NOT DEFINED API_IS_SDK)
	if(CMSDK_IS_ARM)
		#cmsdk_include_target(StratifyOS_iface "${API_CONFIG_LIST}")
		cmsdk_include_target(StratifyOS_crt "${API_CONFIG_LIST}")
	endif()
	cmsdk_include_target(API "${API_CONFIG_LIST}")
	cmsdk_include_target(VarAPI "${API_CONFIG_LIST}")
	cmsdk_include_target(PrinterAPI "${API_CONFIG_LIST}")
	cmsdk_include_target(SysAPI "${API_CONFIG_LIST}")
	cmsdk_include_target(ChronoAPI "${API_CONFIG_LIST}")
	cmsdk_include_target(FsAPI "${API_CONFIG_LIST}")
	cmsdk_include_target(ThreadAPI "${API_CONFIG_LIST}")
	cmsdk_include_target(TestAPI "${API_CONFIG_LIST}")
endif()

function(api_add_api_library NAME DEPENDENCIES)
	api_add_api_library_option(${NAME} "${DEPENDENCIES}" "")
endfunction()

function(api_add_api_library_option NAME DEPENDENCIES LIB_OPTION)

	set(LOCAL_NAME ${NAME})


	cmsdk_library_target(RELEASE ${LOCAL_NAME} "${LIB_OPTION}" release ${CMSDK_ARCH})

	#cmsdk_add_subdirectory(PRIVATE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src)
	cmsdk_add_out_of_source_directory(PRIVATE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src ${RELEASE_TARGET}_src)
	cmsdk_add_out_of_source_directory(INTERFACE_SOURCES include ${RELEASE_TARGET}_include)
	#cmsdk_add_subdirectory(INTERFACE_SOURCES include)


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
		${INTERFACE_SOURCES}
		${PRIVATE_SOURCES}
		${CMAKE_CURRENT_SOURCE_DIR}/${LOCAL_NAME}.cmake
		)


	target_include_directories(${RELEASE_TARGET}
		PUBLIC
		$<INSTALL_INTERFACE:include/${LOCAL_NAME}>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		PRIVATE
		)

	cmsdk_library_target(DEBUG ${LOCAL_NAME} "${LIB_OPTION}" debug ${CMSDK_ARCH})
	add_library(${DEBUG_TARGET} STATIC)
	cmsdk_copy_target(${RELEASE_TARGET} ${DEBUG_TARGET})

	target_compile_options(${DEBUG_TARGET}
		PRIVATE
		-Os
		)

	cmsdk_library_add_arch_targets("${DEBUG_OPTIONS}" ${CMSDK_ARCH} "${DEPENDENCIES}")

	target_compile_options(${RELEASE_TARGET}
		PRIVATE
		-Os
		)

	cmsdk_library_add_arch_targets("${RELEASE_OPTIONS}" ${CMSDK_ARCH} "${DEPENDENCIES}")

	install(DIRECTORY include/
		DESTINATION include/${LOCAL_NAME}
		PATTERN CMakelists.txt EXCLUDE)

	install(FILES ${LOCAL_NAME}.cmake
		DESTINATION ${CMSDK_LOCAL_PATH}/cmake/targets)



endfunction()

function(api_add_test_executable NAME RAM_SIZE DEPENDENCIES)

	set(LOCAL_NAME ${NAME})

	cmsdk_app_target(RELEASE ${LOCAL_NAME} "unittest" release ${CMSDK_ARCH})
  message(STATUS "API UnitTest Executable ${RELEASE_TARGET}")
	add_executable(${RELEASE_TARGET})
	add_dependencies(API_test ${RELEASE_TARGET})
	target_sources(${RELEASE_TARGET}
		PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/sl_config.h
		${CMAKE_CURRENT_SOURCE_DIR}/src/UnitTest.hpp
		)

	target_compile_options(${RELEASE_TARGET}
		PRIVATE
		-Os
		)

	set_property(TARGET ${RELEASE_TARGET} PROPERTY CXX_STANDARD 17)

	set(CTEST_OUTPUT_ON_FAILURE ON)

	cmsdk_app_add_arch_targets("${RELEASE_OPTIONS}" "${DEPENDENCIES}" ${RAM_SIZE})

	target_compile_options(${RELEASE_TARGET}
		PRIVATE
		-Os
		)

	if(CMSDK_IS_LINK)
		cmsdk_add_test(${LOCAL_NAME} ${LIB_OPTION}unittest release)
	endif()

endfunction()
