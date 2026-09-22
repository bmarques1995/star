cmake_minimum_required(VERSION 3.28)

project(Starlang VERSION 0.1.0)

option(STAR_BUILD_CLI "Build the command line interface" ON)
option(STAR_BUILD_TESTS "Build tests" ON)

option(STAR_ENABLE_LLVM_COVERAGE "Enable LLVM source coverage" OFF)
option(STAR_ENABLE_PACKAGING "Enable modify exec name" OFF)
option(BUILD_SHARED_LIBS "Build star as a shared lib" OFF)

set(STAR_COMPILE_ECOSYS)
if(MSVC)
    set(STAR_COMPILE_ECOSYS "msvc")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(STAR_COMPILE_ECOSYS "llvm")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set(STAR_COMPILE_ECOSYS "gcc")
endif()

macro(enable_coverage target)
    if(STAR_ENABLE_LLVM_COVERAGE AND STAR_COMPILE_ECOSYS MATCHES "llvm")
        target_compile_options(${target} PRIVATE -fprofile-instr-generate -fcoverage-mapping)
        target_link_options(${target} PRIVATE -fprofile-instr-generate)
    endif()
endmacro()

function(enable_llvm_memory_debug TARGET_NAME)
	if(STAR_COMPILE_ECOSYS MATCHES "llvm")
		target_compile_options(${TARGET_NAME} PRIVATE -fsanitize=address -fno-omit-frame-pointer)
		target_link_options(${TARGET_NAME} PRIVATE -fsanitize=address)
	endif()
endfunction()

function(set_msvc_debug_improvements TARGET_NAME)
    if(MSVC)
        target_compile_options(${TARGET_NAME} PRIVATE
            $<$<CONFIG:Debug>:/Od>
            $<$<CONFIG:Debug>:/Zi>
        )

        target_link_options(${TARGET_NAME} PRIVATE
            $<$<CONFIG:Debug>:/DEBUG>
        )
    endif()
endfunction()

if(VCPKG_PREFIX_PATH AND VCPKG_TARGET_TRIPLET)
    set(CMAKE_PREFIX_PATH "${VCPKG_PREFIX_PATH}")
endif()

include(FetchContent)

set(ARTIFACT_PREFIX ${PROJECT_BINARY_DIR})
if(WIN32)
    set(ARTIFACT_PREFIX ${CMAKE_INSTALL_PREFIX})
endif()

if(USES_VCPKG)
    set(VCPKG_CURRENT_PREFIX ${VCPKG_PREFIX_PATH}/${VCPKG_TARGET_TRIPLET})
    list(APPEND CMAKE_PREFIX_PATH ${VCPKG_CURRENT_PREFIX})
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(VCPKG_CURRENT_PREFIX ${VCPKG_CURRENT_PREFIX}/debug)
    endif()
    if(WIN32)
        set(ARTIFACT_PREFIX ${VCPKG_CURRENT_PREFIX})
    endif()
endif()

# 2. Declare the download location and version details
FetchContent_Declare(
    cmake_helpers
    GIT_REPOSITORY https://github.com/bmarques1995/cmake_helpers.git
    #GIT_TAG        v1.14.0 # Best practice: Use a specific tag or commit hash
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/cmake_helpers
)

# 3. Download the library and make its targets available
FetchContent_MakeAvailable(cmake_helpers)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR};${PROJECT_SOURCE_DIR}/cmake_helpers")

include(target_destination)
include(source_downloader)
include(InstallRequiredSystemLibraries)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

if(STAR_ENABLE_PACKAGING)
    include(cpack_patcher)

    if(WIN32)
        download_remote_files(
        SOURCE_INPUTS 
            "https://media.githubusercontent.com/media/bmarques1995/star_homepage/refs/heads/master/public/banner.png"
            "https://media.githubusercontent.com/media/bmarques1995/star_homepage/refs/heads/master/public/dialog.png"
            "https://media.githubusercontent.com/media/bmarques1995/star_homepage/refs/heads/master/public/favicon.ico"
        SOURCE_BASE_OUTPUT_DIR
            ${PROJECT_BINARY_DIR}
        )
    endif()

    set_cpack_defaults(LICENSE_IN_FILE ${PROJECT_SOURCE_DIR}/LICENSE LICENSE_OUT_FILE ${PROJECT_BINARY_DIR}/LICENSE.txt)
    add_cpack_wix_configs(
        UPGRADE_GUID "C411F940-3D69-482A-A5EC-229F8A734F14"
        UI "StarlangUI"
        PATCH "${PROJECT_SOURCE_DIR}/wix/wix_patch.xml"
        EXTENSIONS "WixToolset.UI.wixext" "WixToolset.Util.wixext"
        EXTRA_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/wix/StarlangUI.wxs" "${CMAKE_CURRENT_SOURCE_DIR}/wix/StarlangInstallOpts.wxs"
        EXTRA_ACTIONS "STARLANG_ADD_TO_PATH"
        ICON ${PROJECT_BINARY_DIR}/favicon.ico
        BANNER ${PROJECT_BINARY_DIR}/banner.png
        DIALOG ${PROJECT_BINARY_DIR}/dialog.png
    )
    add_cpack_unix_packers(
        MAINTAINER "bmarques1995"
        URL "https://github.com/bmarques1995/star_2.git"
        LICENSE BSD-3-Clauses
        DESC "<DESC>"
        COMMENT "<COMMENT>"
        LICENSE_FILE "${PROJECT_SOURCE_DIR}/LICENSE")
    include(CPack)
endif()

add_subdirectory(src)