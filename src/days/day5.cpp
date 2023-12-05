#include "aoc_days.hpp"
#include <vector>

struct SeedRange
{
    long start;
    long length;
};

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

std::vector<SeedRange> update_range(std::vector<SeedRange>& seed_ranges, const std::vector<std::vector<long>>& dst_src_ranges)
{
    std::vector<SeedRange> out_ranges;
    for (size_t seed_idx = 0; seed_idx < seed_ranges.size(); ++seed_idx)
    {
        bool matched = false;
        for (const auto& dst_src_range : dst_src_ranges)
        {
            const SeedRange& range = seed_ranges[seed_idx];
            const long range_end = range.start + (range.length - 1);
            const long src_range_end = dst_src_range[1] + (dst_src_range[2] - 1);
            
            if ((range_end >= dst_src_range[1]) && (src_range_end >= range.start))
            {
                matched = true;
                
                const long intersection_start = std::max(range.start, dst_src_range[1]);
                const long intersection_end = std::min(range_end, src_range_end);
                const long offset_intersection_start = dst_src_range[0] + (intersection_start - dst_src_range[1]);
                const long offset_intersection_length = (intersection_end + 1) - intersection_start;
   
                out_ranges.push_back(SeedRange { .start = offset_intersection_start, .length = offset_intersection_length });
                
                if (intersection_start > range.start)
                    seed_ranges.push_back(SeedRange { .start = range.start, .length = intersection_start - range.start });
                
                if (intersection_end < range_end)
                    seed_ranges.push_back(SeedRange { .start = intersection_end + 1, .length = range_end - intersection_end });
            }
        }
        
        if (!matched)
            out_ranges.push_back(seed_ranges[seed_idx]);
    }
    return out_ranges;
}

void aoc::day5()
{
    std::ifstream file("inputs/day5.txt");
    std::string line;
    std::getline(file, line);
    std::vector<long> seed_values = parse_numbers_from_line(line, 7);
    
    std::vector<SeedRange> seeds_individual;
    std::vector<SeedRange> seeds_ranged;
    for (size_t seed_value_idx = 0; seed_value_idx < seed_values.size(); ++seed_value_idx)
    {
        seeds_individual.push_back(SeedRange { .start = seed_values[seed_value_idx], .length = 1 });
        if (seed_value_idx % 2 == 0)
            seeds_ranged.push_back(SeedRange { .start = seed_values[seed_value_idx], .length = seed_values[seed_value_idx + 1] });
    }
    
    std::vector<SeedRange> updated_seeds_individual = seeds_individual;
    std::vector<SeedRange> updated_seeds_ranged = seeds_ranged;

    std::vector<std::vector<std::vector<long>>> mappings;
    mappings.push_back(std::vector<std::vector<long>>());
    while (std::getline(file, line))
    {
        if (!std::isdigit(line[0]))
        {
            if (!mappings.back().empty())
                mappings.push_back(std::vector<std::vector<long>>());
            continue;
        }
        
        const std::vector<long>& dst_src_range = parse_numbers_from_line(line, 0);
        mappings.back().push_back(dst_src_range);
    }
    
    for (const auto& mapping : mappings)
    {
        updated_seeds_individual = update_range(seeds_individual, mapping);
        updated_seeds_ranged = update_range(seeds_ranged, mapping);
        seeds_individual = updated_seeds_individual;
        seeds_ranged = updated_seeds_ranged;
    }
    
    auto lowest_itr = std::min_element(updated_seeds_individual.begin(), updated_seeds_individual.end(), [](const SeedRange& lhs, const SeedRange& rhs) { return lhs.start < rhs.start; });
    std::cout << "Lowest location: " << long(lowest_itr->start) << std::endl;
    
    lowest_itr = std::min_element(updated_seeds_ranged.begin(), updated_seeds_ranged.end(), [](const SeedRange& lhs, const SeedRange& rhs) { return lhs.start < rhs.start; });
    std::cout << "Lowest location with seed ranges: " << long(lowest_itr->start) << std::endl;
}
