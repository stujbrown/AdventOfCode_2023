#include "aoc_days.hpp"
#include <vector>
#include <numeric>
#include <set>

struct Beam 
{
    int x = 0;
    int y = 0;
    int vel_x = 0;
    int vel_y = 0;
};
inline bool operator<(const Beam& lhs, const Beam& rhs)
{
    return std::tie(lhs.x, lhs.y, lhs.vel_x, lhs.vel_y) < std::tie(rhs.x, rhs.y, rhs.vel_x, rhs.vel_y);
}

void aoc::day16()
{
    std::vector<std::string> map;
    std::string line;
  
    std::ifstream file("inputs/day16.txt");
    while (file >> line)
    map.push_back(line);
    
    std::vector<std::vector<bool>> energised(map.size(), std::vector<bool>(map[0].size(), false));
    std::set<Beam> history;

    std::vector<Beam> beams(1, Beam {.vel_x = 1});
    while (!beams.empty())
    {
        for (size_t beam_idx = 0; beam_idx < beams.size(); ++beam_idx)
        {
            Beam& beam = beams[beam_idx];
            energised[beam.y][beam.x] = true;
            
            bool remove = false;
            if (history.contains(beam))
            {
                remove = true;
            }
            else
            {
                history.insert(beam);
                beam.x += beam.vel_x;
                beam.y += beam.vel_y;
            }

            if (beam.x < 0 || beam.x >= map[0].size()
                || beam.y < 0 || beam.y >= map.size() || remove)
            {
                beams.erase(beams.begin() + beam_idx);
                --beam_idx;
                continue;
            }
            
            const int current_vel_x = beam.vel_x;
            const int current_vel_y = beam.vel_y;
            const char c = map[beam.y][beam.x];
            if (c == '\\')
            {
                if (current_vel_x > 0)
                    beam.vel_y = 1;
                else if (current_vel_x < 0)
                    beam.vel_y = -1;
                
                if (current_vel_y > 0)
                    beam.vel_x = 1;
                else if (current_vel_y < 0)
                    beam.vel_x = -1;
                
                if (current_vel_x != 0)
                    beam.vel_x = 0;
                if (current_vel_y != 0)
                    beam.vel_y = 0;
                    
            }
            else if (c == '/')
            {
                if (current_vel_x > 0)
                    beam.vel_y = -1;
                else if (current_vel_x < 0)
                    beam.vel_y = 1;
                
                if (current_vel_y > 0)
                    beam.vel_x = -1;
                else if (current_vel_y < 0)
                    beam.vel_x = 1;
                
                if (current_vel_x != 0)
                    beam.vel_x = 0;
                if (current_vel_y != 0)
                    beam.vel_y = 0;
            }
            else if (c == '-' && beam.vel_y != 0)
            {
                beam.vel_x = -1;
                beam.vel_y = 0;
                beams.push_back(Beam {.x = beam.x, .y = beam.y, .vel_x = 1});
            }
            else if (c == '|' && beam.vel_x != 0)
            {
                beam.vel_x = 0;
                beam.vel_y = -1;
                beams.push_back(Beam {.x = beam.x, .y = beam.y, .vel_y = 1});
            }
        }
    }
    
    size_t energised_total = 0;
    for (const auto& row : energised)
        energised_total += std::count(row.begin(), row.end(), true);
    
    std::cout << "Energised total: " << energised_total << std::endl;
}
