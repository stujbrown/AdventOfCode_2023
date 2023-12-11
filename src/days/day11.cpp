#include "aoc_days.hpp"
#include <vector>
#include <set>

struct Coord { int x = 0; int y = 0; };
inline bool operator==(const Coord& lhs, const Coord& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
inline bool operator<(const Coord& lhs, const Coord& rhs)
{
    return (lhs.x < rhs.x) || ((lhs.x == rhs.x) && (lhs.y < rhs.y));
}

void aoc::day11()
{
    std::vector<std::string> galaxy_map;
    std::ifstream file("inputs/day11.txt");
    std::string line;
    while (file >> line)
    {
        std::string empty_row(line.size(), '.');
        const bool contains_galaxy = line.find('#') != std::string::npos;
        
        galaxy_map.push_back(line);
        
        if (!contains_galaxy)
            galaxy_map.push_back(empty_row);
    }
    
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
        {
            for (size_t i = 0; i < galaxy_map.size(); ++i)
                galaxy_map[i].insert(column_idx, ".");
            
            column_idx += 1;
        }
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
    
    size_t total_distances = 0;
    for (const auto& pair : pairs)
    {
        const int distance = std::abs(pair.first.x - pair.second.x) + std::abs(pair.first.y - pair.second.y);
        total_distances += distance;
    }
    
    std::cout << "Total of distances: " << total_distances << std::endl;
}
