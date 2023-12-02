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
    
    #define DAY(number) case number: day##number(); break;
    switch (day_to_run)
    {
        DAY(1);
        DAY(2);
        DAY(3);
        DAY(4);
        DAY(5);
        DAY(6);
        DAY(7);
        DAY(8);
        DAY(9);
        DAY(10);
        DAY(11);
        DAY(12);
        DAY(13);
        DAY(14);
        DAY(15);
        DAY(16);
        DAY(17);
        DAY(18);
        DAY(19);
        DAY(20);
        DAY(21);
        DAY(22);
        DAY(23);
        DAY(24);
        DAY(25);
            
        default:
            std::cout << "Invalid day\n";
            break;
    }
}

}
