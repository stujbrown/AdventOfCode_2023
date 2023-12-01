#include "aoc_days.hpp"

int add_line(const std::string& line, bool allow_alpha)
{
    static const std::vector<std::string> digits_numeric { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    static const std::vector<std::string> digits_numeric_alpha { "1", "2", "3", "4", "5", "6", "7", "8", "9", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    const std::vector<std::string>& digits = allow_alpha ? digits_numeric_alpha : digits_numeric;
    
    size_t first_digit = 0, last_digit = 0;
    size_t best_found = std::string::npos;
    for (size_t i = 0; i < digits.size(); ++i)
    {
        const size_t found = line.find(digits[i]);
        if (found != std::string::npos && found < best_found)
        {
            first_digit = i;
            best_found = found;
        }
    }
    
    last_digit = first_digit;
    best_found = 0;
    for (size_t i = 0; i < digits.size(); ++i)
    {
        const size_t found = line.rfind(digits[i]);
        if (found != std::string::npos && found > best_found)
        {
            last_digit = i;
            best_found = found;
        }
    }
    
    return (((first_digit % 9) + 1) * 10) + (last_digit % 9) + 1;
}

void aoc::day1()
{
    std::ifstream file("inputs/day1.txt");
    std::string line;

    int sum = 0, alpha_sum = 0;
    while (file >> line)
    {
        sum += add_line(line, false);
        alpha_sum += add_line(line, true);
    }
    
    std::cout << "Part 1: " << sum << std::endl;
    std::cout << "Part 2: " << alpha_sum << std::endl;
}
