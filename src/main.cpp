#include "entry.hpp"

#include <stdlib.h>
#include <exception>
#include <iostream>

int main(int argc, const char* argv[])
{
    try 
    {
        aoc::entry(aoc::parse_args(argc, argv));
    } 
    catch (const std::exception& e)
    {
        std::cout << "\nUnhandled exception: " << e.what() << std::endl;
    }

#if _WIN32
    system("pause");
#endif
    return 0;
}
