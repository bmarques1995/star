set(TARGET_NAME star_cli)

file(GLOB_RECURSE STAR_CLI_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE STAR_CLI_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.hpp")

add_executable(${TARGET_NAME} ${STAR_CLI_SRCS} ${STAR_CLI_HDRS})

target_link_libraries(${TARGET_NAME} PUBLIC star)

set_cxx_project_standards(${TARGET_NAME} 20 FALSE)
append_rpath(${TARGET_NAME})
target_installation_behaviour(
	CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
	TARGET_NAME ${TARGET_NAME}
	VERSION ${PROJECT_VERSION}
	PROJECT_NAME ${PROJECT_NAME}
	NAMESPACE "star"
	COMPONENT "star")

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME "star")