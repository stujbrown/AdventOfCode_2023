#include "aoc_days.hpp"
#include <vector>

int scan_map_direction(const std::vector<std::string>& map, bool vertical, int ignore_line = -1)
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
                    is_valid = false;
            }
            else
            {
                for (int j = 0; j < map.size(); ++j)
                {
                    if (map[j][scan_lhs] != map[j][scan_rhs])
                        is_valid = false;
                }
            }
        }
        if (is_valid && i + 1 != ignore_line)
        {
            mirror_pos = i + 1;
            break;
        }
    }
    return mirror_pos;
}

void scan_map(size_t& out_reflection_value, size_t& smudge_fix_reflection_value, const std::vector<std::string>& map)
{
    out_reflection_value = 0;
    smudge_fix_reflection_value = 0;
    
    const int result_h = scan_map_direction(map, false);
    const int result_v = scan_map_direction(map, true);
    if (result_h != -1)
        out_reflection_value = result_h;
    else if (result_v != -1)
        out_reflection_value = result_v * 100;
    
    for (size_t y = 0; y < map.size(); ++y)
    {
        for (size_t x = 0; x < map[0].length(); ++x)
        {
            std::vector<std::string> adjusted_map_copy = map;
            adjusted_map_copy[y][x] = map[y][x] == '.' ? '#' : '.';
            
            const int adjusted_result_h = scan_map_direction(adjusted_map_copy, false, result_h);
            const int adjusted_result_v = scan_map_direction(adjusted_map_copy, true, result_v);
            if (adjusted_result_h != -1)
                smudge_fix_reflection_value = adjusted_result_h;
            if (adjusted_result_v != -1)
                smudge_fix_reflection_value = adjusted_result_v * 100;
        }
    }
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
    
    size_t reflection_summary = 0, smudge_fix_reflection_summary = 0;
    size_t reflection_value = 0, smudge_fix_reflection_value = 0;
    for (const auto& map : maps)
    {
        scan_map(reflection_value, smudge_fix_reflection_value, map);
        reflection_summary += reflection_value;
        smudge_fix_reflection_summary += smudge_fix_reflection_value;
    }
    
    std::cout << "Reflection summary value: " << reflection_summary << std::endl;
    std::cout << "Smudge-fixed reflection summary value: " << smudge_fix_reflection_summary << std::endl;
}
