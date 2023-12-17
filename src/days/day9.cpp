#include "aoc_days.hpp"
#include <vector>
#include <string>

void aoc::day9()
{
    int start_total = 0, end_total = 0;
    
    std::ifstream file("inputs/day9.txt");
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<std::vector<int>> sequences(1);
        size_t start = 0, end = 0;
        while (end != std::string::npos)
        {
            end = line.find(" ", start);
            std::string value_str;
            if (end == std::string::npos)
                value_str = std::string(line.c_str() + start);
            else
                value_str = std::string(line.c_str() + start, end - start);
            
            const int value = std::stoi(value_str);
            sequences[0].push_back(value);
            start = end + 1;
        }
        
        int sequence_idx = 0;
        bool all_zero = false;
        
        while (!all_zero)
        {
            all_zero = true;
            sequences.push_back(std::vector<int>());
            int previous = sequences[sequence_idx][0];
            for (size_t i = 1; i < sequences[sequence_idx].size(); ++i)
            {
                const int current = sequences[sequence_idx][i];
                const int diff = current - previous;
                sequences[sequence_idx + 1].push_back(diff);
                previous = current;
                
                if (diff != 0)
                    all_zero = false;
            }
            ++sequence_idx;
        }
        
        for (sequence_idx = (int)sequences.size() - 1; sequence_idx >= 1; --sequence_idx)
        {
            const std::vector<int>& this_sequence = sequences[sequence_idx];
            std::vector<int>& above_sequence = sequences[sequence_idx - 1];
            
            const int start_increment = this_sequence[0];
            const int end_increment = this_sequence[this_sequence.size() - 1];
            above_sequence.push_back(above_sequence[above_sequence.size() - 1] + end_increment);
            above_sequence.insert(above_sequence.begin(), above_sequence[0] - start_increment);
        }
        
        end_total += sequences[0][sequences[0].size() - 1];
        start_total += sequences[0][0];
    }
    
    std::cout << "End value total: " << end_total << std::endl;
    std::cout << "Start value total: " << start_total << std::endl;
}
