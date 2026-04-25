#pragma once

#include "StarCore.hpp"
#include <iostream>
#include <cstdint>
#include <string>

namespace Star
{
    class STAR_API Debug
    {
    private:
        static void Report(uint32_t line, const std::string& where, const std::string& message);
    public:
        inline static bool s_HadError = false;
        static void Error(uint32_t line, const std::string& message);
    };
}