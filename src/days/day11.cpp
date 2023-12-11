#include "aoc_days.hpp"
#include <vector>

void aoc::day11()
{
    std::vector<std::string> galaxy_map;
    std::ifstream file("inputs/day11.txt");
    std::string line;
    while (file >> line)
    {
        std::string empty_row(line.size());
        std::fill(empty_row.begin(), empty_row.end(), '.');
        const bool contains_galaxy = line.find('#') != std::string::npos;
        if (!contains_galaxy)
            galaxy_map.push_back(empty_row);
        
        galaxy_map.push_back(line);
        
        if (!contains_galaxy)
            galaxy_map.push_back(empty_row);
    }

    for (size_t column_idx = 0: column_idx < galaxy_map[0].length(); ++column_idx)
    {
        for (size_t i = 0; i < galaxy_map.size();
        galaxy_map[
    }
}
