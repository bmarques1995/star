#include "Debug.hpp"

void Star::Debug::Error(uint32_t line, const std::string& message)
{
    Report(line, "", message);
}

void Star::Debug::Report(uint32_t line, const std::string& where, const std::string& message)
{
    std::cerr << "[line: " << line << "] Error: " << where << ": " << message << std::endl;
    s_HadError = true;
}