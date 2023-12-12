#include "aoc_days.hpp"
#include <vector>
#include <map>
#include <numeric>

void match_pattern(size_t& out_matches, const std::string& record, size_t current_pos, const std::vector<int> counts, size_t count_idx, std::map<std::pair<size_t, size_t>, size_t>& memory)
{
    const size_t remaining_counts_sum = std::accumulate(counts.begin() + (count_idx + 1), counts.end(), 0);
    const size_t minimum_later_space_required = remaining_counts_sum + (counts.size() - (count_idx + 1));
    const size_t possible_position_end = record.length() - minimum_later_space_required;
    const size_t required_length = counts[count_idx];
    for (size_t i = current_pos; i < possible_position_end - (required_length - 1); ++i)
    {
        int valid_spaces = 0;
        for (size_t j = i; valid_spaces < counts[count_idx] && j < possible_position_end; ++j)
        {
            if (record[j] == '.')
                break;
            
            ++valid_spaces;
        }
        
        if (valid_spaces == counts[count_idx])
        {
            const char skipped_element = record[i + counts[count_idx]];
            if (skipped_element != '#') // The match just now has to be wrong since this can't be a spacing element
            {
                
                if (count_idx + 1 >= counts.size())
                {
                    bool is_valid = true;
                    for (size_t k = i + counts[count_idx]; k < record.length(); ++k)
                    {
                        if (record[k] == '#')
                            is_valid = false;
                    }
                    
                    if (is_valid)
                        ++out_matches;
                }
                else
                {
                    const size_t next_pos = i + counts[count_idx] + 1;
                    const auto key = std::make_pair(next_pos, count_idx + 1);
                    const auto result = memory.find(key);
                    if (result == memory.end())
                    {
                        size_t matches = 0;
                        match_pattern(matches, record, next_pos, counts, count_idx + 1, memory);
                        memory.insert(std::make_pair(key, matches));
                        out_matches += matches;
                    }
                    else
                        out_matches += result->second;
                }
            }
        }
        
        if (record[i] == '#') // Can't evaluate this from the next position or a required element is omitted
            i = record.size();
    }
}

size_t solve_possibilities(bool expanded)
{
    size_t total_matches = 0;
    
    std::ifstream file("inputs/day12.txt");
    std::string damaged_record_single, other_record_single, damaged_record, other_record;
    while (file >> damaged_record_single && file >> other_record_single)
    {
        damaged_record = damaged_record_single;
        other_record = other_record_single;
        if (expanded)
        {
            for (size_t i = 1; i < 5; ++i)
            {
                damaged_record.append("?");
                damaged_record.append(damaged_record_single);
                other_record.append(",");
                other_record.append(other_record_single);
            }
        }
        
        std::vector<int> damaged_counts;
        size_t parse_offset = 0, str_end = 0;
        while (parse_offset < other_record.length())
        {
            str_end = other_record.find(',', parse_offset);
            damaged_counts.push_back(std::stoi(other_record.substr(parse_offset, str_end - parse_offset)));
            parse_offset = str_end != std::string::npos ? str_end + 1 : std::string::npos;
        }
        
        size_t matches = 0;
        std::map<std::pair<size_t, size_t>, size_t> memory;
        match_pattern(matches, damaged_record, 0, damaged_counts, 0, memory);
        total_matches += matches;
    }
    return total_matches;
}

void aoc::day12()
{
    const size_t total_matches = solve_possibilities(false);
    const size_t total_matches_expanded = solve_possibilities(true);
    
    std::cout << "Total possibilities: " << total_matches << std::endl;
    std::cout << "Total possibilities (expanded): " << total_matches_expanded << std::endl;
}
