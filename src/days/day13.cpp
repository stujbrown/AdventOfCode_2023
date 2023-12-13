#include "aoc_days.hpp"
#include <vector>

int scan_map(const std::vector<std::string>& map, bool vertical)
{
    const int size = vertical ? (int)map.size() : (int)map[0].length();
    int mirror_pos = -1;
    for (int i = 0; i < size - 1; ++i)
    {
        bool is_valid = true;
        for (int scan_lhs = i, scan_rhs = i + 1; scan_lhs >= 0 && scan_rhs < size; --scan_lhs, ++scan_rhs)
        {
            if (vertical)
            {
                if (map[scan_lhs].compare(map[scan_rhs]) != 0)
                {
                    is_valid = false;
                }
            }
            else
            {
                for (int j = 0; j < map.size(); ++j)
                {
                    if (map[j][scan_lhs] != map[j][scan_rhs])
                    {
                        is_valid = false;
                    }
                }
            }
        }
        if (is_valid)
        {
            mirror_pos = i + 1;
            break;
        }
    }
    return mirror_pos;
}

void aoc::day13()
{
    std::vector<std::vector<std::string>> maps(1);
    
    std::ifstream file("inputs/day13.txt");
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            maps.push_back(std::vector<std::string>());
        else
            maps.back().push_back(line);
    }
    
    size_t reflection_summary = 0;
    for (const auto& map : maps)
    {
        const int result_h = scan_map(map, false);
        const int result_v = scan_map(map, true);
        if (result_h != -1)
        {
            reflection_summary += result_h;
        }
        if (result_v != -1)
        {
            reflection_summary += result_v * 100;
        }
    }
    
    std::cout << "Reflection summary value: " << reflection_summary << std::endl;
}
