#include "entry.hpp"
#include "days/days.hpp"

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

std::string read_file(const char* path)
{
    std::ifstream file(path);
    std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return data;
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
        case 1: day1(read_file("inputs/day1.txt")); break;
            
        default:
            std::cout << "Invalid day\n";
            break;
    }
}

}
