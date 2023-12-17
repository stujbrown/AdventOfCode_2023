#include "aoc_days.hpp"
#include <vector>
#include <cctype>
#include <numeric>
#include <string>

long solve_race(long duration, long win_record)
{
    long ways_to_win = 0;
    for (long held_ms = 1; held_ms < duration; ++held_ms)
    {
        const long distance = held_ms * (duration - held_ms);
        if (distance > win_record)
            ++ways_to_win;
    }
    return ways_to_win;
}

void aoc::day6()
{
    std::ifstream file("inputs/day6.txt");
    std::string token;
    int line_idx = -1;
    std::vector<long> durations, times;
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
    
    std::vector<long> ways_to_win;
    for (size_t game_idx = 0; game_idx < durations.size(); ++game_idx)
        ways_to_win.push_back(solve_race(durations[game_idx], times[game_idx]));
    
    std::cout << "Ways to win multiplied: " << std::accumulate(ways_to_win.begin(), ways_to_win.end(), 1, std::multiplies<long>()) << std::endl;
    std::cout << "Ways to win the big race: " << solve_race(std::stol(big_duration_str), std::stol(big_time_str)) << std::endl;
}
