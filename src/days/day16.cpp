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

size_t count_enegised(const std::vector<std::string>& map, int start_x, int start_y)
{
    
    std::vector<std::vector<bool>> energised(map.size(), std::vector<bool>(map[0].size(), false));
    std::set<Beam> history;

    std::vector<Beam> beams(1, Beam {
        .x = start_x,
        .y = start_y,
        .vel_x = (start_x < 0) ? 1 : ((start_x >= map[0].size()) ? -1 : 0),
        .vel_y = (start_y < 0) ? 1 : ((start_y >= map.size()) ? -1 : 0),
    });
    while (!beams.empty())
    {
        for (size_t beam_idx = 0; beam_idx < beams.size(); ++beam_idx)
        {
            Beam& beam = beams[beam_idx];
            if (beam.x >= 0 && beam.x < map[0].size() && beam.y >= 0 && beam.y < map.size())
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
    return energised_total;
}

void aoc::day16()
{
    std::vector<std::string> map;
    std::string line;
  
    std::ifstream file("inputs/day16.txt");
    while (file >> line)
    map.push_back(line);
    
    size_t largest_total = 0;
    const size_t energised_total = count_enegised(map, -1, 0);
    for (size_t x = 0; x < map[0].size(); ++x)
    {
        largest_total = std::max(count_enegised(map, (int)x, -1), largest_total);
        largest_total = std::max(count_enegised(map, (int)x, (int)map.size()), largest_total);
    }
    for (size_t y = 0; y < map.size(); ++y)
    {
        largest_total = std::max(count_enegised(map, -1, (int)y), largest_total);
        largest_total = std::max(count_enegised(map, (int)map[0].size(), (int)y), largest_total);
    }
    
    std::cout << "Energised total: " << energised_total << std::endl;
    std::cout << "Largest energised total: " << largest_total << std::endl;
}
