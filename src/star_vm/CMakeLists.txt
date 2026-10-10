file(GLOB_RECURSE STAR_VM_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS "*.cc")
file(GLOB_RECURSE STAR_VM_HDR_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS "*.hh")

set(TARGET_NAME star_vm)
add_library(${TARGET_NAME} ${STAR_VM_SRC_FILES} ${STAR_VM_HDR_FILES})
set_cxx_project_standards(${TARGET_NAME} 20 FALSE)
set_artifacts_dir(${TARGET_NAME} ${PROJECT_BINARY_DIR})
set_msvc_target_utf8(${TARGET_NAME})
set_msvc_debug_improvements(${TARGET_NAME})
target_include_directories(${TARGET_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
                                                 $<INSTALL_INTERFACE:include/star_vm>)
target_link_libraries(${TARGET_NAME} PRIVATE star)

if(WIN32)
    target_compile_definitions(${TARGET_NAME} PRIVATE STAR_VM_PLATFORM_WINDOWS)
    if(BUILD_SHARED_LIBS)
        target_compile_definitions(${TARGET_NAME} PRIVATE STAR_VM_EXPORTS INTERFACE STAR_VM_IMPORTS)
    endif()
endif()

target_installation_behaviour(TARGET_NAME ${TARGET_NAME}
                              CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
                              VERSION ${PROJECT_VERSION}
                              USE_SHARE TRUE
                              PROJECT_NAME ${PROJECT_NAME}
                              NAMESPACE ${PROJECT_CMAKE_NAMESPACE}
                              COMPONENT ${PROJECT_CMAKE_NAMESPACE}
                              HEADER_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/public/
                              HEADER_OUTPUT include/star_vm)

deploy_runtime_dependencies(${TARGET_NAME})