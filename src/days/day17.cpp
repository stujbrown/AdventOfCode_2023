#include "aoc_days.hpp"
#include <queue>
#include <set>
#include <vector>
#include <tuple>
#include <array>

namespace
{
    enum class Direction : uint8_t { none = 0, north = 1, east = 2, south = 3, west = 4 };
    struct Vec2 { int x = 0, y = 0; };
    struct Node
    {
        Vec2 pos;
        int cost = 0;
        int heat_cost = 0;
        Direction current_direction = Direction::none;
        int steps_in_direction = 0;
        std::shared_ptr<Node> previous;
    };

    struct NodeVisitRecord
    {
        Vec2 pos;
        int cost = 0;
        Direction current_direction = Direction::none;
        int steps_in_direction = 0;
    };

    static const std::array<std::tuple<Vec2, Direction, std::vector<Direction>>, 4> expansion_rules{
        std::make_tuple(Vec2{1, 0}, Direction::east, std::vector<Direction>{Direction::none, Direction::north, Direction::south, Direction::east}),
        std::make_tuple(Vec2{-1, 0}, Direction::west, std::vector<Direction>{Direction::none, Direction::north, Direction::south, Direction::west}),
        std::make_tuple(Vec2{0, 1}, Direction::south, std::vector<Direction>{Direction::none, Direction::east, Direction::south, Direction::west}),
        std::make_tuple(Vec2{0, -1}, Direction::north, std::vector<Direction>{Direction::none, Direction::north, Direction::east, Direction::west}) };

    inline bool operator<(const Vec2& lhs, const Vec2& rhs) { return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y); }
    inline bool operator<(const NodeVisitRecord& lhs, const NodeVisitRecord& rhs) { return std::tie(lhs.pos, lhs.current_direction, lhs.steps_in_direction) < std::tie(rhs.pos, rhs.current_direction, rhs.steps_in_direction); }

    size_t search(const std::vector<std::string>& map, int min_move, int max_move)
    {
        struct NodeComparer {
            bool operator()(const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs) { return lhs->cost > rhs->cost; }
        };

        std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeComparer> open;
        std::set<NodeVisitRecord> visited;

        open.push(std::shared_ptr<Node>(new Node{ .pos {.x = 0, .y = 0} }));

        size_t best_cost = std::numeric_limits<size_t>::max();
        while (!open.empty())
        {
            std::shared_ptr<Node> node = open.top();
            open.pop();
            if (node->pos.x == map[0].size() - 1 && node->pos.y == map.size() - 1)
            {
                if (node->steps_in_direction < min_move)
                    continue;

                best_cost = node->cost;
                break;
            }

            const NodeVisitRecord search_record{
                .pos = node->pos,
                .cost = node->cost,
                .current_direction = node->current_direction,
                .steps_in_direction = node->steps_in_direction };

            if (visited.contains(search_record))
            {
                continue;
            }

            visited.insert(search_record);
            for (const auto& rule : expansion_rules)
            {
                const Vec2 adjustment = std::get<0>(rule);
                const Direction direction = std::get<1>(rule);
                const std::vector<Direction>& valid_start_directions = std::get<2>(rule);
                if (std::find(valid_start_directions.begin(), valid_start_directions.end(), node->current_direction) != valid_start_directions.end())
                {
                    const Vec2 new_pos{ .x = node->pos.x + adjustment.x, .y = node->pos.y + adjustment.y };
                    if (new_pos.x >= 0 && new_pos.x < map[0].size() && new_pos.y >= 0 && new_pos.y < map.size())
                    {
                        int new_steps = 1;
                        if (node->current_direction == direction)
                            new_steps = node->steps_in_direction + 1;
                        else if (node->steps_in_direction < min_move && node->steps_in_direction != 0)
                            continue;

                        if (new_steps <= max_move)
                        {
                            const int dest_cost = map[new_pos.y][new_pos.x] - '0';
                            Node new_node{
                                .pos = new_pos,
                                .cost = node->cost + dest_cost,
                                .heat_cost = node->heat_cost + dest_cost,
                                .current_direction = direction,
                                .steps_in_direction = new_steps,
                                .previous = node };
                            std::shared_ptr<Node> new_node_ptr(new Node(new_node));

                            if (!visited.contains(NodeVisitRecord{
                                    .pos = new_node_ptr->pos,
                                .cost = new_node_ptr->cost,
                                .current_direction = new_node_ptr->current_direction,
                                .steps_in_direction = new_steps }))
                            {
                                open.push(new_node_ptr);
                            }
                        }
                    }
                }
            }
        }
        return best_cost;
    }
}

void aoc::day17()
{
    std::vector<std::string> map;
    std::string line;

    std::ifstream file("inputs/day17.txt");
    while (file >> line)
        map.push_back(line);

    std::cout << "Best path cost for crucible: " << search(map, 0, 3) << std::endl;
    std::cout << "Best path cost for ultra crucible: " << search(map, 4, 10) << std::endl;
}
