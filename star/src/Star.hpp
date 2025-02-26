#pragma once

#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <sstream>
#include "DLLDef.hpp"
#include "Scanner.hpp"

namespace Star
{
    class STARLANG_API Star
    {
    public:
        static void RunFile(const std::string& path);
        static void RunPrompt();
    private:
        static void Run(const std::string& source);
    };
} // namespace My
