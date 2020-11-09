
macro(api_test_executable NAME DIRECTORIES)


	sos_sdk_app_target(RELEASE ${NAME} "" release ${SOS_ARCH})
	add_executable(${RELEASE_TARGET})
	target_sources(${RELEASE_TARGET}
		PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/../common/main.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../${NAME}/src/sl_config.h
		${CMAKE_CURRENT_SOURCE_DIR}/../${NAME}/src/UnitTest.hpp
		)

		target_compile_options(${RELEASE_TARGET}
			PRIVATE
			-Os
			)

	set_property(TARGET ${RELEASE_TARGET} PROPERTY CXX_STANDARD 17)

	foreach(DIRECTORY ${DIRECTORIES})
		target_include_directories(${RELEASE_TARGET}
			PRIVATE
			${CMAKE_SOURCE_DIR}/libraries/${DIRECTORY}/include
			)
	endforeach(DIRECTORY)

	#target_link_libraries(${RELEASE_TARGET}
	#	PRIVATE
	#	mbedtls
	#	)

	target_include_directories(${RELEASE_TARGET}
		PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/../${NAME}/src
		)


	get_target_property(MY_DIR ${RELEASE_TARGET} BINARY_DIR)
	message(STATUS "BINARY DIR for ${RELEASE_TARGET} is ${MY_DIR}")

	if(SOS_IS_LINK)

		sos_sdk_add_test(${NAME} "" release)
		sos_sdk_add_test(${NAME} "" coverage)

		sos_sdk_app_target(COVERAGE ${NAME} "" coverage ${SOS_ARCH})
		add_executable(${COVERAGE_TARGET})
		sos_sdk_copy_target(${RELEASE_TARGET} ${COVERAGE_TARGET})

		set_target_properties(${COVERAGE_TARGET}
			PROPERTIES
			LINK_FLAGS --coverage)

	endif()

	sos_sdk_app_add_arch_targets("${RELEASE_OPTIONS}" "${DIRECTORIES}" ${RAM_SIZE})
	if(SOS_IS_LINK)
		sos_sdk_app_add_arch_targets("${COVERAGE_OPTIONS}" "${DIRECTORIES}" ${RAM_SIZE})
	endif()

	target_compile_options(${RELEASE_TARGET}
		PRIVATE
		-Os
		)

endmacro()
