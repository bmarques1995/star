#include <iostream>
#include "Star.hpp"

#define KB(x) x*1024
#define MB(x) KB(x)*1024
#define GB(x) MB(x)*1024

int main(int argc, char* argv[])
{
    if(argc > 2)
    {
        std::cout << "Usage: " << argv[0] << " <name>.st" << std::endl;
        return EXIT_FAILURE;
    }
    
    if(argc == 2)
    {
        Star::Star::RunFile(argv[1]);
    }
    else
    {
        Star::Star::RunPrompt();
    }
    return EXIT_SUCCESS;
}