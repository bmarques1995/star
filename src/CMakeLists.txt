cmake_minimum_required(VERSION 3.22)

set(TARGET_NAME MyLib)

file(GLOB_RECURSE UTILS_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "code/*.hpp")
file(GLOB_RECURSE UTILS_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "code/*.cpp")

if(WIN32)
	trace_dependency(NAME magic_enum INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/magic_enum.ps1" LIMIT_SEARCH_PATHS)
elseif(LINUX)
    trace_dependency(NAME magic_enum INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/magic_enum.sh" LIMIT_SEARCH_PATHS)
endif()

add_library(${TARGET_NAME} ${BUILD_TYPE} ${UTILS_HDRS} ${UTILS_SRCS})
target_include_directories(${TARGET_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/code>
	$<INSTALL_INTERFACE:include>
	PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/pch>
)
target_link_libraries(${TARGET_NAME} PUBLIC magic_enum::magic_enum)

if(WIN32 AND BUILD_SHARED_LIBS)
	target_compile_definitions(${TARGET_NAME} PRIVATE MY_BUILD_DLL)
	target_compile_definitions(${TARGET_NAME} INTERFACE MY_CONSUME_DLL)
endif()

if(WIN32)
	target_compile_definitions(${TARGET_NAME} PUBLIC MY_WINDOWS)
elseif(LINUX)
    target_compile_definitions(${TARGET_NAME} PUBLIC MY_LINUX)
else()
	message(FATAL_ERROR "Platform not implemented")
endif()

target_precompile_headers(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/pch/pch.hpp)

set_cxx_project_standards(${TARGET_NAME} 20 FALSE)
target_installation_behaviour(
	CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
	TARGET_NAME ${TARGET_NAME}
	VERSION ${PROJECT_VERSION}
	PROJECT_NAME ${PROJECT_NAME}
	NAMESPACE "My"
	HEADER_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/code/
	HEADER_OUTPUT ./include/My)