set(TARGET_NAME star)

add_library(${TARGET_NAME} "Star.hpp"
                           "Star.cpp" 
                           "StarCore.hpp")

target_include_directories(${TARGET_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)