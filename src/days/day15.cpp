#include "aoc_days.hpp"
#include <sstream>
#include <algorithm>
#include <vector>
#include <array>

struct Lens
{
    std::string label;
    int length = -1;
};

int hash_instruction(const std::string_view token)
{
    int current = 0;
    for (size_t i = 0; i < token.length(); ++i)
    {
        const int code = token[i];
        current += code;
        current = current * 17;
        current = current % 256;
    }
    return current;
}

void aoc::day15()
{
    size_t hash_sum = 0;
    std::array<std::vector<Lens>, 256> boxes;
    std::fill(boxes.begin(), boxes.end(), std::vector<Lens>());
    
    std::ifstream file("inputs/day15.txt");
    std::string line, token;
    while (file >> line)
    {
        std::stringstream token_stream(line, std::ios_base::in);
        while (std::getline(token_stream, token, ','))
        {
            hash_sum += hash_instruction(token);
            
            size_t symbol_pos = token.find('=');
            symbol_pos = (symbol_pos != std::string::npos) ? symbol_pos : token.find('-');
            std::string label(token.c_str(), 0, symbol_pos);
            const int box_index = hash_instruction(label);
            std::vector<Lens>& box = boxes[box_index];
            
            if (symbol_pos != std::string::npos && token[symbol_pos] == '=')
            {
                std::string operand(token.c_str() + symbol_pos + 1, token.length() - (symbol_pos + 1));
                const int length = std::stoi(operand);
                
                auto existing_itr = std::find_if(box.begin(), box.end(), [label](const Lens& lens) {
                    return lens.label.compare(label) == 0;
                });
                if (existing_itr != box.end())
                    (*existing_itr) = Lens { .label = label, .length = length };
                else
                    box.push_back(Lens { .label = label, .length = length });
            }
            else
            {
                box.erase(std::remove_if(box.begin(), box.end(), [label](const Lens& lens) {
                    return lens.label.compare(label) == 0;
                }), box.end());
            }
        }
    }
    
    size_t focal_sum = 0;
    for (size_t box_idx = 0; box_idx < boxes.size(); ++box_idx)
        for (size_t lens_idx = 0; lens_idx < boxes[box_idx].size(); ++lens_idx)
            focal_sum += (box_idx + 1) * (lens_idx + 1) * boxes[box_idx][lens_idx].length;
    
    std::cout << "Hash sum: " << hash_sum << std::endl;
    std::cout << "Focal power sum: " << focal_sum << std::endl;
    
}
