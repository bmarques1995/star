set(TARGET_NAME star)

file(GLOB_RECURSE STAR_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE STAR_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.hpp")

add_library(${TARGET_NAME} ${STAR_SRCS} ${STAR_HDRS})

target_include_directories(${TARGET_NAME} PUBLIC #$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                                                 $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
                                                 $<INSTALL_INTERFACE:include/star>)

if(WIN32)
	if(BUILD_SHARED_LIBS)	
		target_compile_definitions(${TARGET_NAME} PUBLIC STAR_WINDOWS_SHARED
												  PRIVATE STAR_EXPORTS
												  INTERFACE STAR_IMPORTS)
	endif()
endif()

set_cxx_project_standards(${TARGET_NAME} 20 FALSE)
append_rpath(${TARGET_NAME})
target_installation_behaviour(
	CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
	TARGET_NAME ${TARGET_NAME}
	VERSION ${PROJECT_VERSION}
	PROJECT_NAME ${PROJECT_NAME}
	NAMESPACE "star"
	COMPONENT "star"
    HEADER_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/
    HEADER_OUTPUT include/star)