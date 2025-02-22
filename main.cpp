#include <iostream>
#include "My.hpp"

int main(int argc, char* argv[])
{
    if(argc > 2)
    {
        std::cout << "Usage: " << argv[0] << " <name>.my" << std::endl;
        return EXIT_FAILURE;
    }
    
    if(argc == 2)
    {
        My::My::runFile(argv[1]);
    }
    else
    {
        My::My::runPrompt();
    }
    return EXIT_SUCCESS;
}