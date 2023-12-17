#include "aoc_days.hpp"
#include <map>
#include <vector>
#include <numeric>
#include <string>

namespace
{
struct Node
{
    std::string left;
    std::string right;
};

size_t solve(const std::map<std::string, std::unique_ptr<Node>>& nodes, const std::string& instructions, bool use_multipath)
{
    std::vector<const Node*> path_starts;
    if (use_multipath)
    {
        for (const auto& node : nodes)
        {
            if (node.first.ends_with('A'))
                path_starts.push_back(node.second.get());
        }
    }
    else
        path_starts.push_back(nodes.find("AAA")->second.get());
    
    std::vector<size_t> steps_to_next_end(path_starts.size(), 0);
    for (size_t current_idx = 0; current_idx < path_starts.size(); ++current_idx)
    {
        size_t next_instruction = 0;
        size_t steps_taken = 0;
        
        const Node* current = path_starts[current_idx];
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
                if (steps_to_next_end[current_idx] == steps_taken) // Big dumb assumption that it'll start looping (this input does)
                    break;
                
                steps_to_next_end[current_idx] = steps_taken;
                steps_taken = 0;
            }
            current = next ? nodes.find(*next)->second.get() : nullptr;
            next_instruction = (next_instruction + 1) % instructions.length();
        }
    }
    
    size_t lcm = 0;
    for (const size_t steps : steps_to_next_end)
    {
        if (lcm == 0)
            lcm = steps;
        else
            lcm = std::lcm(steps, lcm);
    }
    return lcm;
}
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
