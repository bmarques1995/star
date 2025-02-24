#include "Debug.hpp"

void My::Debug::error(uint32_t line, const std::string& message)
{
    report(line, "", message);
}

void My::Debug::report(uint32_t line, const std::string& where, const std::string& message)
{
    std::cerr << "[line: " << line << "] Error: " << where << ": " << message << std::endl;
    hadError = true;
}