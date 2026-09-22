add_subdirectory(star)

if(STAR_BUILD_CLI)
    add_subdirectory(star_cli)
    add_subdirectory(repl)    
endif()

if(STAR_BUILD_TESTS)
    add_subdirectory(tests)
endif()
