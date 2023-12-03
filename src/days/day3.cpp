#include "aoc_days.hpp"
#include <string>
#include <vector>
#include <set>
#include <charconv>

void aoc::day3()
{
    struct NumRecord
    {
        int number = 0;
        int row = 0;
        int start = 0;
        int end = 0;
    };

    std::ifstream file("inputs/day3.txt");
    std::string line;
    std::vector<std::string> rows;
    std::vector<NumRecord> numbers;

    while (file >> line)
        rows.push_back(line);

    int part_sum = 0, part_ratio_sum = 0;
    for (size_t row_idx = 0; row_idx < rows.size(); ++row_idx)
    {
        size_t num_start = 0;
        bool previous_was_number = false;
        for (size_t i = 0; i < rows[row_idx].length(); ++i)
        {
            const bool is_num = rows[row_idx][i] >= '0' && rows[row_idx][i] <= '9';
            const bool is_at_end = i == rows[row_idx].length() - 1;
            if (!is_num || is_at_end)
            {
                if (previous_was_number)
                {
                    const int num = std::stoi(std::string(rows[row_idx].data() + num_start, (i - num_start) + (is_at_end ? 1 : 0)));
                    NumRecord record{ .number = (int)num, .row = (int)row_idx, .start = (int)num_start, .end = (int)i + (is_at_end ? 1 : 0) };
                    numbers.push_back(record);
                }
                num_start = i + 1;
            }
            previous_was_number = is_num;
        }
    }

    std::set<int> counted_parts;
    for (size_t row_idx = 0; row_idx < rows.size(); ++row_idx)
    {
        for (size_t i = 0; i < rows[row_idx].length(); ++i)
        {
            const char c = rows[row_idx][i];
            if (c != '.' && (c < '0' || c > '9'))
            {
                std::vector<int> part_values;
                for (const NumRecord& num : numbers)
                {
                    if ((abs(num.row - (int)row_idx) <= 1) && ((int)i >= num.start - 1 && (int)i <= num.end))
                    {
                        part_sum += counted_parts.contains(num.number) ? 0 : num.number;
                        counted_parts.insert(num.number);
                        part_values.push_back(num.number);
                    }
                }

                if (c == '*' && part_values.size() == 2)
                    part_ratio_sum += part_values[0] * part_values[1];
            }
        }
    }

    std::cout << "Part sum: " << part_sum << std::endl;
    std::cout << "Part ratio sum: " << part_ratio_sum << std::endl;
}