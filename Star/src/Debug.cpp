#include "Debug.hpp"

void Star::Debug::Report(uint32_t line, const std::string& where, const std::string& message)
{
    s_HadError = true;
    std::cerr << "[line " << line << "] Error in " << where << ": " << message << std::endl;
}

void Star::Debug::Error(uint32_t line, const std::string& message)
{
    Report(line, "", message);
}
