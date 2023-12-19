#include "aoc_days.hpp"
#include <vector>
#include <string>

namespace
{
    struct Point
    {
        int64_t x = 0, y = 0;
    };

    size_t solve(bool decode_alt_instructions)
    {
        std::vector<Point> corner_points(1, Point{ 0, 0 });

        int64_t current_x = 0, current_y = 0;

        std::ifstream file("inputs/day18.txt");
        std::string direction_str, distance_str, colour_str;
        size_t total_length = 0;
        while (file >> direction_str && file >> distance_str && file >> colour_str)
        {
            int64_t distance = 0;
            if (decode_alt_instructions)
            {
                const char dir_decode_table[4] = { 'R', 'D', 'L', 'U' };
                const std::string decoded_dist_str = colour_str.substr(2, 5);
                distance = std::stoi(decoded_dist_str, 0, 16);
                direction_str = dir_decode_table[colour_str[7] - '0'];
            }
            else
                distance = std::stoi(distance_str);

            int64_t move_x = 0, move_y = 0;
            if (direction_str[0] == 'R')
                move_x = 1;
            else if (direction_str[0] == 'L')
                move_x = -1;
            else if (direction_str[0] == 'U')
                move_y = -1;
            else if (direction_str[0] == 'D')
                move_y = 1;

            const int64_t new_x = current_x + ((int64_t)distance * move_x);
            const int64_t new_y = current_y + ((int64_t)distance * move_y);
            corner_points.push_back(Point{ .x = new_x, .y = new_y });

            current_x += (distance * move_x);
            current_y += (distance * move_y);
            total_length += distance;

            double area = 0;
            for (size_t i = 0; i < corner_points.size(); ++i)
            {
                const int64_t j = (i + 1) % (int64_t)corner_points.size();
                area += 0.5 * double((corner_points[i].x * corner_points[j].y) - (corner_points[j].x * corner_points[i].y));
            }
            area += total_length / 2 + 1;

            return (size_t)area;
        }
    }
}

void aoc::day18()
{
    std::cout << "Size within trench area: " << solve(false) << std::endl;
    std::cout << "Size within trench area (decoded from colour): " << solve(true) << std::endl;
}