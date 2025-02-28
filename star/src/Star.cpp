#include "Star.hpp"

namespace fs = std::filesystem;

void Star::Star::RunFile(const std::string& path)
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
    Run(source);
    if(Debug::s_HadError)
    {
        std::exit(65);
    }
}

void Star::Star::RunPrompt()
{
    std::string line;
    std::cout << "star> ";
    for(;;)
    {
        if(!std::getline(std::cin, line) || line == "exit")
            break;
        Run(line);
        std::cout << "star> ";
    }
}

void Star::Star::Run(const std::string& source)
{
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    if (Debug::s_HadError)
    {
        return;
    }
    
    Parser parser(tokens);
    auto expression = parser.Parse();

    if (Debug::s_HadError)
    {
        return;
    }
    
    // for(auto& token : tokens)
    // {
    //     std::cout << token.ToString() << std::endl;
    // }
}