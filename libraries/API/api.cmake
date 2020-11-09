

macro(api_target NAME DIRECTORIES)

	project(
		${NAME}
		VERSION ${STRATIFYAPI_PROJECT_VERSION}
		LANGUAGES CXX)

	install(DIRECTORY include/ DESTINATION include/${NAME})

	sos_sdk_add_subdirectory(PRIVATE_SOURCES src)
	sos_sdk_add_subdirectory(PUBLIC_SOURCES	${CMAKE_CURRENT_SOURCE_DIR}/include)
	set(FORMAT_LIST ${PRIVATE_SOURCES} ${PUBLIC_SOURCES})

	sos_sdk_library_target(RELEASE ${NAME} "" release ${SOS_ARCH})
	add_library(${RELEASE_TARGET} STATIC)

	set_property(TARGET ${RELEASE_TARGET} PROPERTY CXX_STANDARD 17)

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

	target_include_directories(${RELEASE_TARGET}
		INTERFACE
		$<INSTALL_INTERFACE:include/${NAME}>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
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
	if(IS_API)

		if(SOS_IS_LINK)
			# this doesn't need to be added as a directory, just a dependency
			list(APPEND LOCAL_DIRECTORIES StratifyOS)
		else()
			list(APPEND LOCAL_DIRECTORIES StratifyOS_crt)
		endif()
		message(STATUS "DIRS ${LOCAL_DIRECTORIES}")
	endif()

	target_include_directories(${RELEASE_TARGET}
		PUBLIC
		$<INSTALL_INTERFACE:include/${NAME}>
		PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		)

	sos_sdk_library_target(DEBUG ${NAME} "" debug ${SOS_ARCH})
	add_library(${DEBUG_TARGET} STATIC)
	sos_sdk_copy_target(${RELEASE_TARGET} ${DEBUG_TARGET})

	if(SOS_IS_LINK)
		sos_sdk_library_target(COVERAGE ${NAME} "" coverage ${SOS_ARCH})
		add_library(${COVERAGE_TARGET} STATIC)
		sos_sdk_copy_target(${RELEASE_TARGET} ${COVERAGE_TARGET})

		target_compile_options(${COVERAGE_TARGET}
			PUBLIC
			--coverage
			)

		sos_sdk_library_add_arch_targets("${COVERAGE_OPTIONS}" ${SOS_ARCH} "${LOCAL_DIRECTORIES}")

		get_target_property(MY_DIR ${COVERAGE_TARGET} BINARY_DIR)

		get_target_property(SOURCES ${COVERAGE_TARGET} SOURCES)

		foreach(SOURCE ${SOURCES})
			get_filename_component(FILE_NAME ${SOURCE} NAME)
			list(APPEND GCOV_SOURCES ${MY_DIR}/CMakeFiles/${COVERAGE_TARGET}.dir/src/${FILE_NAME}.gcda)
		endforeach()

		add_custom_target(coverage_mkdir_${COVERAGE_TARGET}
			COMMAND mkdir -p ${CMAKE_SOURCE_DIR}/coverage/${COVERAGE_TARGET}
			)

		add_custom_target(coverage_${COVERAGE_TARGET}
			COMMAND gcov ${GCOV_SOURCES}
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/coverage/${COVERAGE_TARGET}
			DEPENDS coverage_mkdir_${COVERAGE_TARGET}
			)

		add_custom_target(clean_coverage_${COVERAGE_TARGET}
			COMMAND rm -f ${GCOV_SOURCES}
			DEPENDS coverage_mkdir_${COVERAGE_TARGET}
			)

	endif()

	sos_sdk_library_add_arch_targets("${RELEASE_OPTIONS}" ${SOS_ARCH} "${LOCAL_DIRECTORIES}")
	sos_sdk_library_add_arch_targets("${DEBUG_OPTIONS}" ${SOS_ARCH} "${LOCAL_DIRECTORIES}")

	if(IS_API)
		get_target_property(RELEASE_LINK_LIBS ${RELEASE_TARGET} INTERFACE_LINK_LIBRARIES)
		get_target_property(DEBUG_LINK_LIBS ${DEBUG_TARGET} INTERFACE_LINK_LIBRARIES)
	endif()

	add_custom_target(
		${NAME}_format
		COMMAND /usr/local/bin/clang-format
		-i
		--verbose
		${FORMAT_LIST}
		)

endmacro()
