#include "entry.hpp"
#include "days/aoc_days.hpp"

#include <stdlib.h>
#include <fstream>

namespace aoc
{

Args parse_args(int num_args, const char* args[])
{
    int day_to_run = -1;
    if (num_args > 1)
    {
        day_to_run = atoi(args[1]);
    }
    return Args { .day_to_run = day_to_run };
}

void entry(const Args& args)
{
    int day_to_run = args.day_to_run;
    if (day_to_run <= 0)
    {
        std::cout << "Run day: ";
        std::cin >> day_to_run;
        std::cout << std::endl;
    }
    
    switch (day_to_run)
    {
        case 1: day1(); break;
            
        default:
            std::cout << "Invalid day\n";
            break;
    }
}

}
