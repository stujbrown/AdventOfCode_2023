#include "aoc_days.hpp"
#include <map>
#include <vector>
#include <numeric>

struct Node
{
    std::string left;
    std::string right;
};


size_t solve(const std::map<std::string, std::unique_ptr<Node>>& nodes, const std::string& instructions, bool use_multipath)
{
    std::vector<const Node*> current_nodes;
    if (use_multipath)
    {
        for (const auto& node : nodes)
        {
            if (node.first.ends_with('A'))
                current_nodes.push_back(node.second.get());
        }
    }
    else
        current_nodes.push_back(nodes.find("AAA")->second.get());
    
    struct EndPathNode
    {
        size_t steps_to_next;
        std::shared_ptr<EndPathNode> next;
    };
    
    std::vector<std::shared_ptr<EndPathNode>> path_positions;
    for (size_t current_idx = 0; current_idx < current_nodes.size(); ++current_idx)
    {
        std::map<std::pair<std::string, size_t>, std::shared_ptr<EndPathNode>> end_nodes;
        size_t next_instruction = 0;
        size_t steps_taken = 0;
        std::shared_ptr<EndPathNode> start(new EndPathNode { .steps_to_next = 0 });
        std::shared_ptr<EndPathNode> last_node = start;
        path_positions.push_back(start);
        
        const Node* current = current_nodes[current_idx];
        while (current != nullptr)
        {
            ++steps_taken;
            
            const std::string* next = nullptr;
            if (instructions[next_instruction] == 'L')
                next = &current->left;
            else if (instructions[next_instruction] == 'R')
                next = &current->right;
            
            if (use_multipath ? next->ends_with('Z') : next->compare("ZZZ") == 0)
            {
                auto found_node = end_nodes.find(std::make_pair(*next, next_instruction));
                if (found_node != end_nodes.end())
                {
                    last_node->next = found_node->second;
                    last_node->steps_to_next = steps_taken;
                    break;
                }
                
                std::shared_ptr<EndPathNode> new_node(new EndPathNode { .steps_to_next = 0 });
                end_nodes.insert(std::make_pair(std::make_pair(*next, next_instruction), new_node));
                last_node->next = new_node;
                last_node->steps_to_next = steps_taken;
                last_node = new_node;
                
                steps_taken = 0;
            }
            current = nodes.find(*next)->second.get();
            next_instruction = (next_instruction + 1) % instructions.length();
        }
    }
    
    size_t lcm = 0;
    for (const auto& node : path_positions)
    {
        if (lcm == 0)
            lcm = node->next->next->steps_to_next;
        else
            lcm = std::lcm(node->next->next->steps_to_next, lcm);
    }
    return lcm;
}

void aoc::day8()
{
    std::ifstream file("inputs/day8.txt");
    std::string instructions, line;
    file >> instructions;

    std::map<std::string, std::unique_ptr<Node>> nodes;
    while (std::getline(file, line))
    {
        if (line.compare("") == 0)
            continue;
        
        auto name = line.substr(0, 3);
        auto left = line.substr(7, 3);
        auto right = line.substr(12, 3);
        nodes.insert(std::make_pair(name, new Node { .left = left, .right = right }));
    }
  
    const size_t num_steps = solve(nodes, instructions, false);
    const size_t num_steps_multipath = solve(nodes, instructions, true);
    
    std::cout << "Num steps to reach ZZZ: " << num_steps << std::endl;
    std::cout << "Num steps to reach ZZZ with multiple paths: " << num_steps_multipath << std::endl;
}
