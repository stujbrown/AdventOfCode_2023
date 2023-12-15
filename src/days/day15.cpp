#include "aoc_days.hpp"
#include <sstream>

void aoc::day15()
{
    size_t hash_sum = 0;
    
    std::ifstream file("inputs/day15.txt");
    std::string line, token;
    while (file >> line)
    {
        std::stringstream token_stream(line, std::ios_base::in);
        while (std::getline(token_stream, token, ','))
        {
            int current = 0;
            for (size_t i = 0; i < token.length(); ++i)
            {
                const int code = token[i];
                current += code;
                current = current * 17;
                current = current % 256;
                
            }
            
            hash_sum += current;
        }
    }
    
    std::cout << "Hash sum: " << hash_sum << std::endl;
    
}
