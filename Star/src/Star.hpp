#pragma once

#include "StarCore.hpp"

#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace Star
{
    class STAR_API Entrypoint
    {
    private:
        static void Run(const std::string& source);
    public:
        static void RunFile(const std::string& filePath);
        static void RunPrompt();
    };
}