#include "aoc_days.hpp"

void aoc::day9()
{
    std::ifstream file("inputs/day9.txt");
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<std::vector<int>> sequences;
        size_t start = 0, end = 0;
        while (end != std::string::npos)
        {
            end = line.find(" ", start);
            if (end != std::string::npos)
            {
                std::string value_str(line.begin() + start, end - start);
                const int value = std::stoi(value_str);
                sequence.push_back(value);
            }
        }

        
    }
{
