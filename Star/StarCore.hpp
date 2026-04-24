#pragma once

#ifdef STAR_WINDOWS_SHARED
    #ifdef STAR_EXPORTS
        #define STAR_API __declspec(dllexport)
    #else
        #define STAR_API __declspec(dllimport)
    #endif
#else
    #define STAR_API
#endif