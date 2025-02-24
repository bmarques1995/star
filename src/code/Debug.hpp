#pragma once

#include "DLLDef.hpp"
#include <iostream>
#include <cstdint>

namespace My
{
    class MYLANG_API Debug
    {
    private:
        static void report(uint32_t, const std::string&, const std::string&);
    public:
        inline static bool hadError = false;
        static void error(uint32_t line, const std::string& message);
    };
}