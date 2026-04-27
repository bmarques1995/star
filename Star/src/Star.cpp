#include "Star.hpp"

namespace fs = std::filesystem;

void Star::Entrypoint::Run(const std::string& source)
{
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    for (auto& t : tokens)
    {
        std::cout << t.ToString() << "\n";
    }
    if(Debug::s_HadError)
    {
        std::exit(65);
    }
}

void Star::Entrypoint::RunFile(const std::string& filePath)
{
    if (!fs::exists(filePath))
    {
        std::cerr << "File not found: " << filePath << std::endl;
        std::exit(66);
    }

    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file)
    {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        std::exit(66);
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(size);
    file.read(buffer.data(), size);
    if (!file)
    {
        std::cerr << "Failed to read file: " << filePath << std::endl;
        std::exit(77);
    }

    std::string content(buffer.begin(), buffer.end());
    Run(content);
}

void Star::Entrypoint::RunPrompt()
{
    std::string line;
    std::cout << "star> ";
    std::getline(std::cin, line);
    bool exitCommand = line.compare("exit") == 0 || line.compare("quit") == 0;
    while (!exitCommand)
    {
        Run(line);
        std::cout << "star> ";
        std::getline(std::cin, line);
        exitCommand = line.compare("exit") == 0 || line.compare("quit") == 0;
    }
}
