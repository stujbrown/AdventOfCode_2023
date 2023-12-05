#include "aoc_days.hpp"
#include <vector>
#include <cctype>

std::vector<long> parse_numbers_from_line(const std::string& str, size_t start_pos)
{
    std::vector<long> values;
    for (size_t start_idx = start_pos; start_idx < str.length(); ++start_idx)
    {
        const size_t end_idx = str.find(" ", start_idx, 1);
        const long value = std::stol(str.substr(start_idx, std::min(end_idx, str.length()) - start_idx));
        values.push_back(value);
        start_idx = (end_idx != std::string::npos) ? end_idx : str.length();
    }
    return values;
}

void aoc::day5()
{
    std::ifstream file("inputs/day5.txt");
    std::string line;
    std::getline(file, line);
    std::vector<long> seeds = parse_numbers_from_line(line, 7);
    std::vector<bool> seed_upated(seeds.size(), false);
    
    bool is_new_group = true;
    while (std::getline(file, line))
    {
        if (!std::isdigit(line[0]))
        {
            is_new_group = true;
            std::fill(seed_upated.begin(), seed_upated.end(), false);
    
            continue;
        }
        
        const std::vector<long>& dst_src_range = parse_numbers_from_line(line, 0);
        for (size_t seed_idx = 0; seed_idx < seeds.size(); ++seed_idx)
        {
            if (!seed_upated[seed_idx] &&
                seeds[seed_idx] >= dst_src_range[1] && seeds[seed_idx] < dst_src_range[1] + dst_src_range[2])
            {
                const long range_offset = seeds[seed_idx] - dst_src_range[1];
                seeds[seed_idx] = dst_src_range[0] + range_offset;
                seed_upated[seed_idx] = true;
            }
        }
    }
    
    const auto lowest_itr = std::min_element(seeds.begin(), seeds.end());
    std::cout << "Lowest location: " << *lowest_itr << std::endl;
}
