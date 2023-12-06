#include "aoc_days.hpp"
#include <vector>
#include <cctype>

long solve(const std::vector<long>& durations, const std::vector<long>& times)
{
    long ways_to_win_multiplied = 0;
    for (size_t game_idx = 0; game_idx < durations.size(); ++game_idx)
    {
        long ways_to_win = 0;
        for (long held_ms = 1; held_ms < durations[game_idx]; ++held_ms)
        {
            const long distance = held_ms * (durations[game_idx] - held_ms);
            if (distance > times[game_idx])
            {
                ++ways_to_win;
            }
        }
        
        if (ways_to_win_multiplied == 0)
            ways_to_win_multiplied = ways_to_win;
        else
            ways_to_win_multiplied *= ways_to_win > 0 ? ways_to_win : 1;
    }
    
    return ways_to_win_multiplied;
}

void aoc::day6()
{
    std::ifstream file("inputs/day6.txt");
    std::string token;
    int line_idx = -1;
    std::vector<long> durations, times, combimed_duration, combined_time;
    std::string big_duration_str, big_time_str;
    while (file >> token)
    {
        if (std::isalpha(token[0]))
            ++line_idx;
        else
        {
            (line_idx == 0 ? durations : times).push_back(std::stol(token));
            (line_idx == 0 ? big_duration_str : big_time_str) += token;
        }
    }
    combimed_duration.push_back(std::stol(big_duration_str));
    combined_time.push_back(std::stol(big_time_str));
    
    const long ways_to_win_multiplied = solve(durations, times);
    const long ways_to_win_big_race = solve(combimed_duration, combined_time);
    
    std::cout << "Ways to win multiplied: " << ways_to_win_multiplied << std::endl;
    std::cout << "Ways to win the big race: " << ways_to_win_big_race << std::endl;
}
