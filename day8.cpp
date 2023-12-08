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
    
    std::ifstream file("input/day8.txt");
    std::string instructions, line;
    file >> instructions;

    std::map<std::string, Node> nodes;
    while (std::getline(file, line))
    {
        
    }
  
}
