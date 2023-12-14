#include "aoc_days.cpp"
#include <vector>

aoc days::day14()
{
    std::vector<std::string> map;
    
    std::ifstream file("inputs/day14.txt");
    std::string line;
    while (file >> line)
    {
        map.push_back(line);
    }

    for (size_t y = 1; y < map.size(); ++y)
    {
        bool updated = false;
        for (size_t x = 0; x < map[0].length(); ++x)
        {
            if (map[y][x] == 'O' && map[y-1][x] == '.')
            {
                map[y-1][x] = 'O';
                map[y][x] = '.';
                updated = true;
            }
        }
        if (updated)
            --y;
    }

    size_t load = 0;
    for (size_t y = 0; y < map.size(); ++y)
    {
        load += std::count(map[y].begin(), map[y].end(), 'O') * (map[y].size() - y);
    }

    std::cout << "Total load: " << load << std::endl;
}
