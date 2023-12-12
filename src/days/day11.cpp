#include "aoc_days.hpp"
#include <vector>
#include <set>

struct Coord { int x = 0; int y = 0; };
inline bool operator<(const Coord& lhs, const Coord& rhs)
{
    return (lhs.x < rhs.x) || ((lhs.x == rhs.x) && (lhs.y < rhs.y));
}

size_t count_distances(const std::vector<std::pair<Coord, Coord>>& pairs, const std::vector<size_t>& row_offsets, const std::vector<size_t>& column_offsets, size_t expansion_amount)
{
    size_t total_distances = 0;
    for (const auto& pair : pairs)
    {
        const Coord start { .x = pair.first.x + int(column_offsets[pair.first.x] * expansion_amount),
            .y = pair.first.y + int(row_offsets[pair.first.y] * expansion_amount) };
        
        const Coord end { .x = pair.second.x + int(column_offsets[pair.second.x] * expansion_amount),
            .y = pair.second.y + int(row_offsets[pair.second.y] * expansion_amount) };
        
        total_distances += std::abs(start.x - end.x) + std::abs(start.y - end.y);
    }
    return total_distances;
}

void aoc::day11()
{
    std::vector<size_t> row_offsets;
    std::vector<size_t> column_offsets;
    
    std::vector<std::string> galaxy_map;
    std::ifstream file("inputs/day11.txt");
    std::string line;
    size_t offset = 0;
    while (file >> line)
    {
        std::string empty_row(line.size(), '.');
        if (line.find('#') == std::string::npos)
            offset += 1;
        
        galaxy_map.push_back(line);
        row_offsets.push_back(offset);
    }
    
    offset = 0;
    for (size_t column_idx = 0; column_idx < galaxy_map[0].length(); ++column_idx)
    {
        bool contains_galaxy = false;
        for (size_t i = 0; i < galaxy_map.size(); ++i)
        {
            if (galaxy_map[i][column_idx] == '#')
            {
                contains_galaxy = true;
                break;
            }
        }
        
        if (!contains_galaxy)
            offset += 1;
            
        column_offsets.push_back(offset);
    }
    
    std::set<std::pair<Coord, Coord>> recorded_pairs;
    std::vector<std::pair<Coord, Coord>> pairs;
    
    for (size_t y = 0; y < galaxy_map.size(); ++y)
    {
        for (size_t x = 0; x < galaxy_map[0].length(); ++x)
        {
            if (galaxy_map[y][x] == '#')
            {
                for (size_t other_y = 0; other_y < galaxy_map.size(); ++other_y)
                {
                    for (size_t other_x = 0; other_x < galaxy_map[0].length(); ++other_x)
                    {
                        if (galaxy_map[other_y][other_x] == '#' && (x != other_x || y != other_y))
                        {
                            const Coord lhs { .x = (int)x, .y = (int)y};
                            const Coord rhs { .x = (int)other_x, .y = (int)other_y};
                            if (!recorded_pairs.contains(std::make_pair(lhs, rhs)))
                            {
                                recorded_pairs.insert(std::make_pair(lhs, rhs));
                                recorded_pairs.insert(std::make_pair(rhs, lhs));
                                pairs.push_back(std::make_pair(lhs, rhs));
                            }
                        }
                    }
                }
            }
        }
    }
    
    const size_t total_distances = count_distances(pairs, row_offsets, column_offsets, 1);
    const size_t total_distances_big = count_distances(pairs, row_offsets, column_offsets, 1000000 - 1);
    
    std::cout << "Total of distances: " << total_distances << std::endl;
    std::cout << "Total of distances for the big universe: " << total_distances_big << std::endl;
}
