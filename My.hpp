#pragma once

#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <sstream>

namespace My
{
    class My
    {
    public:
        static void runFile(const std::string& path);
        static void runPrompt();
    private:
        static void run(const std::string& source);
    };
} // namespace My
