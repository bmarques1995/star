#pragma once

#ifdef STAR_BUILD_DLL
#define STARLANG_API __declspec(dllexport)
#elif STAR_CONSUME_DLL
#define STARLANG_API __declspec(dllimport)
#else
#define STARLANG_API
#endif