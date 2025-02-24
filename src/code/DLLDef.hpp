#pragma once

#ifdef MY_BUILD_DLL
#define MYLANG_API __declspec(dllexport)
#elif MY_CONSUME_DLL
#define MYLANG_API __declspec(dllimport)
#else
#define MYLANG_API
#endif