#include "aoc_days.hpp"
#include <vector>

struct Beam 
{
    int x = 0;
    int y = 0;
    int vel_x = 0;
    int vel_y = 0;
};

void aoc::day16()
{
    std::vector<std::string> map;
    std::strimg line;
  
    std::ifstream file("inputs/day16.txt");
    while (file >> line)
    map.push_back(line);

    std::vector<Beam> beams(1, Beam {.vel_x = 0});
    while ()
    {
        for (Beam& beam : beams)
        {
            beam.x += beam.vel_x;
            beam.y += beam.vel_y;

            if (beam.x < 0 || beam.x >= map[0].size()
                || beam.y < 0 || beam.y >= map.size())
            {
                continue;
            }
            const char c = map[beam.y][beam.x];
            if (c == '\')
            {
                if 
            }
        }
    }
}
