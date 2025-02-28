#pragma once

#include "DLLDef.hpp"
#include "Token.hpp"
#include <iostream>
#include <cstdint>

namespace Star
{
    class STARLANG_API Debug
    {
    private:
        static void Report(uint32_t, const std::string&, const std::string&);
    public:
        inline static bool s_HadError = false;
        static void Error(uint32_t line, const std::string& message);
        static void Error(Token token, const std::string& message);
    };
}