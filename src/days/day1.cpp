#include "aoc_days.hpp"

int add_line(const std::string& line, bool allow_alpha)
{
    static const std::vector<std::string> digits_numeric { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    static const std::vector<std::string> digits_numeric_alpha { "1", "2", "3", "4", "5", "6", "7", "8", "9", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    const std::vector<std::string>& digits = allow_alpha ? digits_numeric_alpha : digits_numeric;
    
    int first_digit = -1, last_digit = -1;
    for (size_t i = 0; i < line.size(); ++i)
    {
        for (size_t digit_index = 0; digit_index < digits.size(); ++digit_index)
        {
            const int digit = digit_index % 9;
            if (strncmp(line.c_str() + i, digits[digit_index].c_str(), digits[digit_index].length()) == 0)
            {
                if (first_digit == -1)
                    first_digit = digit;
                last_digit = digit;
            }
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
