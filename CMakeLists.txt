cmake_minimum_required(VERSION 3.28)

project(Star VERSION 0.1.0)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_helpers")

include(dep_tracer)
include(target_destination)

add_subdirectory(Star)
add_subdirectory(StarCLI)