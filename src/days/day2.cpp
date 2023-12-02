#include "aoc_days.hpp"
#include <array>

void aoc::day2()
{
    std::array<size_t, 3> max_counts {0, 0, 0};
    
    std::ifstream file("inputs/day2.txt");
    std::string line;
    while (file >> line)
    {
        const size_t separator_idx = line.find_first_of(':');
        const std::string_view id(line.c_str() + 4, separator_idx - 4);

        size_t string_start = 0;
        for (size_t i = seperator_idx; i < line.length(); ++i)
            {
                
            }
    }
}
