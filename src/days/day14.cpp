#include "aoc_days.hpp"
#include <vector>
#include <list>

enum class Direction : uint8_t { north = 0, west = 1, south = 2, east = 3 };

void roll_rocks(std::vector<std::string>& map, Direction dir)
{
    if (dir == Direction::north || dir == Direction::south)
    {
        size_t loop_start = (dir == Direction::north) ? 1 : map.size() - 2;
        size_t loop_end = (dir == Direction::north) ? map.size() : static_cast<size_t>(-1);
        size_t loop_inc = (dir == Direction::north) ? 1 : -1;
        for (size_t y = loop_start; y != loop_end; y += loop_inc)
        {
            bool updated = false;
            for (size_t x = 0; x < map[0].length(); ++x)
            {
                if (map[y][x] == 'O' && map[y - loop_inc][x] == '.')
                {
                    map[y - loop_inc][x] = 'O';
                    map[y][x] = '.';
                    updated = true;
                }
            }
            if (updated)
            {
                if (dir == Direction::north)
                    y = (y > 2) ? y - 2 : 0;
                else
                    y = std::min(map.size() - 1, y + 2);
            }
        }
    }
    else if (dir == Direction::east || dir == Direction::west)
    {
        size_t loop_start = (dir == Direction::west) ? 1 : map[0].length() - 2;
        size_t loop_end = (dir == Direction::west) ? map[0].length() : static_cast<size_t>(-1);
        size_t loop_inc = (dir == Direction::west) ? 1 : -1;
        for (size_t x = loop_start; x != loop_end; x += loop_inc)
        {
            bool updated = false;
            for (size_t y = 0; y < map.size(); ++y)
            {
                if (map[y][x] == 'O' && map[y][x - loop_inc] == '.')
                {
                    map[y][x - loop_inc] = 'O';
                    map[y][x] = '.';
                    updated = true;
                }
            }
            if (updated)
            {
                if (dir == Direction::west)
                    x = (x > 2) ? x - 2 : 0;
                else
                    x = std::min(map[0].length() - 1, x + 2);
            }
        }
    }
}

void aoc::day14()
{
    std::vector<std::string> map;
    
    std::ifstream file("inputs/day14.txt");
    std::string line;
    while (file >> line)
        map.push_back(line);

    int current_direction = (int)Direction::north;
    roll_rocks(map, (Direction)current_direction++);

    size_t load = 0, load_after_spin = 0;
    for (size_t y = 0; y < map.size(); ++y)
        load += std::count(map[y].begin(), map[y].end(), 'O') * (map[y].size() - y);
    
    std::list<std::vector<std::string>> previous_records;
    for (size_t i = 0; i < 1000000000; ++i)
    {
        for (; current_direction < 4; ++current_direction)
            roll_rocks(map, (Direction)current_direction);
        
        size_t record_idx = 0;
        auto itr = previous_records.begin();
        while (itr != previous_records.end())
        {
            if ((*itr) == map)
            {
                const int loop_length = (record_idx + 1);
                const size_t s = (1000000000 - i) % loop_length;
                if (s == 1)
                {
                    i = 1000000000 + 1;
                    previous_records.clear();
                    break;
                }
            }
            ++itr;
            ++record_idx;
        }
        
        previous_records.push_front(map);
        
        if (previous_records.size() > 50)
            previous_records.pop_back();
        
        current_direction = 0;
    }
    
    
    for (size_t y = 0; y < map.size(); ++y)
        load_after_spin += std::count(map[y].begin(), map[y].end(), 'O') * (map[y].size() - y);

    std::cout << "Total load: " << load << std::endl;
    std::cout << "Total load after spin cycle: " << load_after_spin << std::endl;
}
