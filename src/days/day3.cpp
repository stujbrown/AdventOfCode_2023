#include "aoc_days.hpp"
#include <string>
#include <vector>

void aoc::day3()
{
    std::ifstream file("inputs/day3.txt");
    std::string line;
    std::vector<std::string> rows;

    while (file >> line)
        rows.push_back(line);

    int part_sum = 0;
    for (size_t row_idx = 0; row_idx < rows.size(); ++row_idx)
    {
        const std::string_view row = rows[row_idx];

        size_t num_start = 0;
        bool previous_was_number = false;
        for (size_t i = 0; i < row.length(); ++i)
        {
            const bool is_num = row[i] >= '0' && row[i] <= '9';
            const bool is_at_end = i == row.length() - 1;
            if (!is_num || is_at_end)
            {
                if (previous_was_number)
                {
                    const std::string num_str(row.data() + num_start, (i - num_start) + (is_at_end ? 1 : 0));
                    const int num = std::stoi(num_str);
                    bool is_part = false;

                    for (size_t scan_row_idx = std::max((int)row_idx - 1, 0); scan_row_idx < row_idx + 2 && scan_row_idx < rows.size(); ++scan_row_idx)
                    {
                        for (size_t scan_idx = std::max((int)num_start - 1, 0); scan_idx < i + 1 && scan_idx < rows[scan_row_idx].length(); ++scan_idx)
                        {
                            const char c = rows[scan_row_idx][scan_idx];
                            if (c != '.' && (c < '0' || c > '9'))
                            {
                                is_part = true;
                            }
                        }
                    }

                    if (is_part)
                    {
                        part_sum += num;
                        std::cout << "Part: " << num << std::endl;
                    }
                }
                num_start = i + 1;
            }

            previous_was_number = is_num;
        }
    }
    std::cout << "Valid part sum: " << part_sum << std::endl;
}