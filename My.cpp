#include "My.hpp"

namespace fs = std::filesystem;

void My::My::runFile(const std::string& path)
{
    if(!fs::exists(path))
    {
        std::cerr << "File not found: " << path << std::endl;
        std::exit(66);
    }
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file)
    {
        std::cerr << "Permission denied to file: " << path << std::endl;
        std::exit(66);
    }
    
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(size);

    if (!file.read(buffer.data(), size))
    {
        std::cerr << "Error reading file: " << path << std::endl;
        std::exit(77);
    }

    std::string source(buffer.begin(), buffer.end());
    run(source);
}

void My::My::runPrompt()
{
    std::string line;
    std::cout << "my> ";
    for(;;)
    {
        if(!std::getline(std::cin, line) || line == "exit")
            break;
        run(line);
        std::cout << "my> ";
    }
}

void My::My::run(const std::string& source)
{
    std::cout << source << std::endl;
}