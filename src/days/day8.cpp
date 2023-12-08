#include "aoc_days.hpp"
#include <map>
#include <vector>

void aoc::day8()
{
    struct Node
    {
        std::map<std::string, std::string> destinations;
        std::string left;
        std::string right;
    };
    
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
  
    size_t num_steps = 0;
    size_t next_instruction = 0;
    const Node* current = nodes["AAA"].get();
    while (current)
    {
        const std::string* next = nullptr;
        if (instructions[next_instruction] == 'L')
            next = &current->left;
        else if (instructions[next_instruction] == 'R')
            next = &current->right;
        
        ++num_steps;
        
        if (next->compare("ZZZ") == 0)
        {
            current = nullptr;
        }
        else
        {
            current = nodes.find(*next)->second.get();
            next_instruction = (next_instruction + 1) % instructions.length();
        }
    }
    
    std::cout << "Num steps to reach ZZZ: " << num_steps << std::endl;
}
