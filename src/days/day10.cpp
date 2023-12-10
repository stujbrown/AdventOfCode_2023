#include "aoc_days.hpp"
#include <vector>
#include <set>
#include <map>
#include <numeric>

struct Coord { int x; int y; };
enum class Direction : uint8_t { Left = 0, Right = 1, Up = 2, Down = 3, None = 4 };

inline bool operator<(const Coord& lhs, const Coord& rhs)
{
    return (lhs.x < rhs.x) || ((lhs.x == rhs.x) && (lhs.y < rhs.y));
}

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
    if (pos.y < map.size() && valid_directions.find(current)->second[(size_t)Direction::Down])
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
    
    std::shared_ptr<SearchNode> end_node;
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
                end_node = std::shared_ptr<SearchNode>(new SearchNode { .pos = start_pos, .previous = current, .num_steps_taken = current->num_steps_taken + 1, .dir = next->dir });
                break;
            }
            stack.push_back(next);
        }
    }
    
    // Walk the route and seed the flood-fill using left-hand positions
    std::vector<Coord> fill_stack;
    std::set<Coord> visited;
    SearchNode* current = end_node.get();
    while (current != nullptr)
    {
        const Coord& from = current->pos;
        visited.insert(from);
        current = current->previous.get();
        if (current != nullptr)
        {
            const int dir_x = current->pos.x - from.x;
            const int dir_y = current->pos.y - from.y;
            if (dir_x > 0 && from.y > 0)
                fill_stack.push_back(Coord {.x = from.x, .y = from.y - 1});
            else if (dir_x < 0 && from.y < map.size())
                fill_stack.push_back(Coord {.x = from.x, .y = from.y + 1});
            else if (dir_y > 0 && from.x < map[0].length())
                fill_stack.push_back(Coord {.x = from.x + 1, .y = from.y});
            else if (dir_y < 0 && from.x > 0)
                fill_stack.push_back(Coord {.x = from.x - 1, .y = from.y});
        }
    }
    
    std::vector<std::vector<int>> fill_map(map.size(), std::vector<int>(map[0].length(), 0));
    while (!fill_stack.empty())
    {
        const Coord next = fill_stack[fill_stack.size() - 1];
        fill_stack.pop_back();
        if (!visited.contains(next))
        {
            fill_map[next.y][next.x] = 1;
            visited.insert(next);
            if (next.x > 0)
                fill_stack.push_back(Coord {.x = next.x - 1, .y = next.y});
            if (next.x < fill_map[0].size())
                fill_stack.push_back(Coord {.x = next.x + 1, .y = next.y});
            if (next.y > 0)
                fill_stack.push_back(Coord {.x = next.x, .y = next.y - 1});
            if (next.y < fill_map.size())
                fill_stack.push_back(Coord {.x = next.x, .y = next.y + 1});
        }
    }
    
    size_t included_cells = 0;
    for (size_t y = 0; y < fill_map.size(); ++y)
        included_cells += std::accumulate(fill_map[y].begin(), fill_map[y].end(), 0);
    
    std::cout << "Furthest distance: " << furthest_point << std::endl;
    std::cout << "Included cells: " << included_cells << std::endl;
}
