set(TARGET_NAME star_cli)

add_executable(${TARGET_NAME} main.cpp)

target_link_libraries(${TARGET_NAME} PUBLIC star)

set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 20)