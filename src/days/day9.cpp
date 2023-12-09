#include "aoc_days.hpp"

void aoc::day9()
{
    std::ifstream file("inputs/day9.txt");
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<std::vector<int>> sequences(1);
        size_t start = 0, end = 0;
        while (end != std::string::npos)
        {
            end = line.find(" ", start);
            if (end != std::string::npos)
            {
                std::string value_str(line.begin() + start, end - start);
                const int value = std::stoi(value_str);
                sequences[0].push_back(value);
            }
        }

        size_t sequence_idx = 0;
        bool all_zero = false;

        
        
        
        while (!all_zero)
        {
            sequences.push_back(std::vector<int>());
            int previous = sequences[sequence_idx];
            for (size_t i = 0; i < sequences[sequence_idx].size(); ++i)
            {
                const int current = sequences[sequence_idx][i];
                const int diff = previous - current;
                if (
                previous = current;
            }
        }

        
    }
{
