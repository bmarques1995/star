#include <cstdlib>
#include "Star.hpp"

int main(int argc, char** argv)
{    
    if(argc > 2)
    {
        std::cerr << "Usage: " << argv[0] << " file.st" << std::endl;
        return EXIT_FAILURE;
    }

    if(argc == 2)
    {
        Star::Entrypoint::RunFile(argv[1]);
    }
    else
    {
        Star::Entrypoint::RunPrompt();
    }
    return EXIT_SUCCESS;
}