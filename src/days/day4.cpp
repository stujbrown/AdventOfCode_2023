#include "aoc_days.hpp"
#include <set>
#include <vector>
#include <numeric>

void aoc::day4()
{
    int point_total = 0;
    
    std::vector<int> card_multipliers;
    size_t current_game = 0;
    
    std::ifstream file("inputs/day4.txt");
    std::string line;
    while (std::getline(file, line))
    {
        card_multipliers.resize(std::max(card_multipliers.size(), current_game + 1), 1);
        
        std::set<int> win_numbers;
        std::set<int> my_numbers;
        
        const size_t start_idx = line.find(": ") + 2;
        bool is_win_input = true;
        for (size_t i = start_idx; i < line.length(); i += 3)
        {
            if (line[i] == '|')
            {
                --i;
                is_win_input = false;
                continue;
            }
            std::string num_str(line.data() + i, 2);
            (is_win_input ? win_numbers : my_numbers).insert(std::stoi(num_str));
        }
        
        std::vector<int> matches;
        std::set_intersection(win_numbers.begin(), win_numbers.end(), my_numbers.begin(), my_numbers.end(), std::back_inserter(matches));
        
        if (matches.size() > 0)
        {
            card_multipliers.resize(std::max(card_multipliers.size(), current_game + 1 + matches.size()), 1);
            
            for (size_t j = 0; j < matches.size(); ++j)
                card_multipliers[current_game + 1 + j] += card_multipliers[current_game];
            
            point_total += std::pow(2, matches.size() - 1);
        }
        ++current_game;
    }
    
    std::cout << "Point total: " << point_total << std::endl;
    std::cout << "Total cards: " << std::accumulate(card_multipliers.begin(), card_multipliers.end(), 0) << std::endl;
}
