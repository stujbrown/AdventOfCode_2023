#include "aoc_days.hpp"
#include <array>
#include <vector>
#include <string>

void aoc::day2()
{
    std::ifstream file("inputs/day2.txt");
    std::string line;

    const std::array<std::string_view, 3> colours{ "red", "green", "blue" };
    int possible_game_sum = 0;
    int power_sum = 0;

    while (std::getline(file, line, '\n'))
    {
        std::array<int, 3> max_counts{ 0, 0, 0 };

        const size_t separator_idx = line.find_first_of(':');
        const std::string id(line.c_str() + 5, separator_idx - 5);

        size_t value_start = separator_idx + 1;
        for (size_t i = separator_idx; i < line.length(); ++i)
        {
            if (line[i] == ',' || line[i] == ';')
            {
                value_start = i + 1;
                continue;
            }

            for (size_t colour_idx = 0; colour_idx < colours.size(); ++colour_idx)
            {
                if (strncmp(line.c_str() + i, colours[colour_idx].data(), colours[colour_idx].length()) == 0)
                {
                    std::string num_str(line.c_str() + value_start, i - value_start);
                    num_str.erase(std::remove_if(num_str.begin(), num_str.end(), [](auto c) { return std::isspace((unsigned char)c); }), num_str.end());
                    const int value = std::stoi(num_str);
                    max_counts[colour_idx] = std::max(max_counts[colour_idx], value);

                    i += colours[colour_idx].length() - 1;
                    break;
                }
            }
        }

        if (max_counts[0] <= 12 && max_counts[1] <= 13 && max_counts[2] <= 14)
            possible_game_sum += std::stoi(id);

        power_sum += max_counts[0] * max_counts[1] * max_counts[2];
    }

    std::cout << "Sum of possible games: " << possible_game_sum << std::endl;
    std::cout << "Sum of powers: " << power_sum << std::endl;
}
