cmake_minimum_required(VERSION 3.22)

set(TARGET_NAME ${PROJECT_NAME})

file(GLOB_RECURSE LAUNCHER_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.hpp")
file(GLOB_RECURSE LAUNCHER_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")

add_executable(${TARGET_NAME} ${LAUNCHER_HDRS} ${LAUNCHER_SRCS})
target_link_libraries(${TARGET_NAME} PUBLIC star_lib)

set_cxx_project_standards(${TARGET_NAME} 20 FALSE)

add_custom_target(copy_assets ALL
			COMMAND ${CMAKE_COMMAND} -E copy_directory
			"${CMAKE_CURRENT_SOURCE_DIR}/assets"
			${CMAKE_PREFIX_PATH}/bin/assets
			COMMENT "Copying star script into binary directory")
add_dependencies(${TARGET_NAME} copy_assets)