#include "aoc_days.hpp"
#include <vector>
#include <set>
#include <map>

struct Coord { int x; int y; };
enum class Direction : uint8_t { Left = 0, Right = 1, Up = 2, Down = 3, None = 4 };

struct SearchNode
{
    Coord pos = {-1, -1};
    const std::shared_ptr<SearchNode> previous;
    int num_steps_taken = 0;
    Direction dir = Direction::None;
};

static const std::map<char, std::array<bool, 4>> valid_directions {
    {'S', {true, true, true, true}},
    {'|', {false, false, true, true}},
    {'-', {true, true, false, false}},
    {'F', {false, true, false, true}},
    {'7', {true, false, false, true}},
    {'J', {true, false, true, false}},
    {'L', {false, true, true, false}},
};
static const std::array<std::vector<char>, 4> valid_conections {
    std::vector<char> {'-', 'F', 'L', 'S'},
    std::vector<char> {'-', '7', 'J', 'S'},
    std::vector<char> {'|', 'F', '7', 'S'},
    std::vector<char> {'|', 'J', 'L', 'S'}
};

void expand_direction(std::vector<std::shared_ptr<SearchNode>>& results, const std::vector<std::string>& map, const std::shared_ptr<SearchNode>& current_node, int change_x, int change_y, Direction dir)
{
    const Coord& pos = current_node->pos;
    const Coord next_pos {.x = pos.x + change_x, .y = pos.y + change_y};
    if (current_node->previous == nullptr || (current_node->previous->pos.x != next_pos.x || current_node->previous->pos.y != next_pos.y))
    {
        const char next = map[next_pos.y][next_pos.x];
        const auto& connections = valid_conections[(size_t)dir];
        if (std::find(connections.begin(), connections.end(), next) != connections.end())
        {
            results.push_back(std::shared_ptr<SearchNode>(new SearchNode {
                .pos = Coord { .x = next_pos.x, .y = next_pos.y },
                .previous = current_node,
                .num_steps_taken = current_node->num_steps_taken + 1,
                .dir = dir}));
        }
    }
}

void expand(std::vector<std::shared_ptr<SearchNode>>& results, const std::vector<std::string>& map, const std::shared_ptr<SearchNode>& current_node)
{
    results.clear();
    const Coord& pos = current_node->pos;
    const char current = map[pos.y][pos.x];
    
    if (pos.x > 0 && valid_directions.find(current)->second[(size_t)Direction::Left])
        expand_direction(results, map, current_node, -1, 0, Direction::Left);
    if (pos.x < map[0].length() && valid_directions.find(current)->second[(size_t)Direction::Right])
        expand_direction(results, map, current_node, 1, 0, Direction::Right);
    if (pos.y > 0 && valid_directions.find(current)->second[(size_t)Direction::Up])
        expand_direction(results, map, current_node, 0, -1, Direction::Up);
    if (pos.x < map.size() && valid_directions.find(current)->second[(size_t)Direction::Down])
        expand_direction(results, map, current_node, 0, 1, Direction::Down);
}

void aoc::day10()
{
    std::vector<std::string> map;
    Coord start_pos;
    
    std::ifstream file("inputs/day10.txt");
    std::string line;
    while (file >> line)
    {
        map.push_back(line);
        
        const size_t result = line.find('S');
        if (result != std::string::npos)
            start_pos = Coord {.x = (int)result, .y = (int)map.size() - 1};
    }
    
    size_t furthest_point = 0;
    
    std::vector<std::shared_ptr<SearchNode>> stack;
    std::vector<std::shared_ptr<SearchNode>> expanded;
    stack.push_back(std::shared_ptr<SearchNode>(new SearchNode {.pos = start_pos, .dir = Direction::None}));
    
    while (!stack.empty())
    {
        const auto current = stack[stack.size() - 1];
        stack.pop_back();
        
        expand(expanded, map, current);
        for (const auto& next : expanded)
        {
            const Coord& next_pos = next->pos;
            if (next_pos.x == start_pos.x && next_pos.y == start_pos.y)
            {
                furthest_point = int((((double)current->num_steps_taken + 1) + 0.5) / 2.0);
                break;
            }
            stack.push_back(next);
        }
    }
    
    
    std::cout << "Furthest distance: " << furthest_point << std::endl;
}
