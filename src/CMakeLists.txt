add_subdirectory(star)
add_subdirectory(star_vm)

if(STAR_BUILD_CLI)
    add_subdirectory(star_cli)
    add_subdirectory(repl)    
endif()

if(STAR_BUILD_TESTS)
    add_subdirectory(tests)
endif()
