#pragma once

#ifdef STAR_VM_PLATFORM_WINDOWS
    #ifdef STAR_VM_EXPORTS
        #define STAR_VM_API __declspec(dllexport)
    #elif defined(STAR_VM_IMPORTS)
        #define STAR_VM_API __declspec(dllimport)
    #else
        #define STAR_VM_API
    #endif
#else
    #define STAR_VM_API
#endif