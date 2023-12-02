#include "aoc_days.hpp"
#include <array>
#include <vector>
#include <charconv>
#include <string>

void aoc::day2()
{
    int possible_game_sum = 0;

    const std::array<std::string_view, 3> colours { "red", "green", "blue" };
    std::vector<int> possible_games;

    std::ifstream file("inputs/day2.txt");
    std::string line;
    while (std::getline(file, line, '\n'))
    {
        std::array<size_t, 3> max_counts{ 0, 0, 0 };

        const size_t separator_idx = line.find_first_of(':');
        const std::string_view id(line.c_str() + 5, separator_idx - 5);

        size_t value_start = separator_idx + 1;
        for (size_t i = separator_idx; i < line.length(); ++i)
        {
            if (line[i] == ',')
            {
                value_start = i + 1;
            }
            else if (line[i] == ';')
            {
                value_start = i + 1;
                // Rounds are currently irrelevant
            }
            else
            {
                for (size_t colour_idx = 0; colour_idx < colours.size(); ++colour_idx)
                {
                    if (strncmp(line.c_str() + i, colours[colour_idx].data(), colours[colour_idx].length()) == 0)
                    {
                        std::string num_str(line.c_str() + value_start, i - value_start);
                        num_str.erase(std::remove_if(num_str.begin(), num_str.end(), std::isspace), num_str.end());
                        const int value = std::stoi(num_str);
                        max_counts[colour_idx] = std::max(max_counts[colour_idx], (size_t)value);

                        i += colours[colour_idx].length() - 1;
                        break;
                    }
                }
            }
        }

        if (max_counts[0] <= 12 && max_counts[1] <= 13 && max_counts[2] <= 14)
        {
            int game_id = 0;
            std::from_chars(id.data(), id.data() + id.length(), game_id);
            possible_games.push_back(game_id);

            possible_game_sum += game_id;
        }
    }

    std::cout << "Sum of possible games: " << possible_game_sum << std::endl;
}
