#include "aoc_days.hpp"
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <numeric>

namespace
{
    struct Rule
    {
        std::string id;
        std::vector<std::string> conditions;
    };

    struct Part
    {
        enum class PartRatingType : uint8_t { X = 0, M, A, S, NUM_ENTRIES };
        std::array<int, (int)PartRatingType::NUM_ENTRIES> entries;
    };

    struct PartRanges
    {
        std::array<std::pair<int64_t, int64_t>, (int)Part::PartRatingType::NUM_ENTRIES> ranges;
    };

    size_t count_possibilities(const PartRanges& ranges)
    {
        const size_t in1 = (ranges.ranges[0].second + 1) - ranges.ranges[0].first;
        const size_t in2 = (ranges.ranges[1].second + 1) - ranges.ranges[1].first;
        const size_t in3 = (ranges.ranges[2].second + 1) - ranges.ranges[2].first;
        const size_t in4 = (ranges.ranges[3].second + 1) - ranges.ranges[3].first;
        return in1 * in2 * in3 * in4;
    }

    size_t solve_possibilities_recursive(const std::vector<Rule>& rules, const Rule* current_rule, PartRanges ranges)
    {
        size_t total_accepted = 0;
        for (size_t i = 0; i < current_rule->conditions.size(); ++i)
        {
            const std::string& condition = current_rule->conditions[i];
            const size_t operator_less_index = condition.find('<');
            const size_t operator_greater_index = condition.find('>');
            const size_t result_index = condition.find(':');
            if (result_index != std::string::npos)
            {
                Part::PartRatingType type = Part::PartRatingType::X;
                switch (condition[0])
                {
                case 'x': type = Part::PartRatingType::X; break;
                case 'm': type = Part::PartRatingType::M; break;
                case 'a': type = Part::PartRatingType::A; break;
                case 's': type = Part::PartRatingType::S; break;
                }
                const size_t operator_index = std::min(operator_less_index, operator_greater_index);
                const auto r = condition.substr(operator_index + 1, result_index - (operator_index + 1));
                const int64_t operand = std::stoi(r);

                PartRanges new_ranges = ranges;
                if (operator_less_index != std::string::npos)
                {
                    if (operand < new_ranges.ranges[(int)type].first)
                        continue;

                    new_ranges.ranges[(int)type].second = std::min(new_ranges.ranges[(int)type].second, operand - 1);
                    ranges.ranges[(int)type].first = std::max(ranges.ranges[(int)type].first, operand);
                }
                else
                {
                    if (operand > new_ranges.ranges[(int)type].second)
                        continue;

                    new_ranges.ranges[(int)type].first = std::max(new_ranges.ranges[(int)type].first, operand + 1);
                    ranges.ranges[(int)type].second = std::min(ranges.ranges[(int)type].second, operand);
                }
                const bool range_invalidated = ranges.ranges[(int)type].first > ranges.ranges[(int)type].second;

                const std::string to = condition.substr(result_index + 1);
                if (to.compare("A") == 0)
                    total_accepted += count_possibilities(new_ranges);
                else if (to.compare("R") != 0)
                {
                    const Rule* next_rule = &*std::find_if(rules.begin(), rules.end(), [to](const Rule& rule) {
                        return rule.id.compare(to) == 0;
                        });
                    total_accepted += solve_possibilities_recursive(rules, next_rule, new_ranges);
                }
                if (range_invalidated)
                    break;
            }
            else
            {
                const std::string to = condition.substr(result_index + 1);
                if (to.compare("A") == 0)
                    total_accepted += count_possibilities(ranges);
                else if (to.compare("R") != 0)
                {
                    const Rule* next_rule = &*std::find_if(rules.begin(), rules.end(), [to](const Rule& rule) {
                        return rule.id.compare(to) == 0;
                        });
                    total_accepted += solve_possibilities_recursive(rules, next_rule, ranges);
                }
            }
        }
        return total_accepted;
    }

    size_t solve_possible_parts(const std::vector<Rule>& rules)
    {
        const Rule* current_rule = &*std::find_if(rules.begin(), rules.end(), [](const Rule& rule) {
            return rule.id.compare("in") == 0;
            });

        PartRanges ranges;
        ranges.ranges[0] = std::make_pair(1, 4000);
        ranges.ranges[1] = std::make_pair(1, 4000);
        ranges.ranges[2] = std::make_pair(1, 4000);
        ranges.ranges[3] = std::make_pair(1, 4000);
        return solve_possibilities_recursive(rules, current_rule, ranges);
    }

    size_t solve_part_list(const std::vector<Rule>& rules, const std::vector<Part>& parts)
    {
        size_t part_value_total = 0;
        for (const Part& part : parts)
        {
            const Rule* current_rule = &*std::find_if(rules.begin(), rules.end(), [](const Rule& rule) {
                return rule.id.compare("in") == 0;
                });

            PartRanges ranges;
            ranges.ranges[0] = std::make_pair(part.entries[0], part.entries[0]);
            ranges.ranges[1] = std::make_pair(part.entries[1], part.entries[1]);
            ranges.ranges[2] = std::make_pair(part.entries[2], part.entries[2]);
            ranges.ranges[3] = std::make_pair(part.entries[3], part.entries[3]);
            if (solve_possibilities_recursive(rules, current_rule, ranges) > 0)
            {
                part_value_total += std::accumulate(part.entries.begin(), part.entries.end(), 0);
            }
        }
        return part_value_total;
    }
}

void aoc::day19()
{
    std::vector<Rule> rules;
    std::vector<Part> parts;

    std::ifstream file("inputs/day19.txt");
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            break;

        const size_t id_end = line.find('{');


        Rule rule{ .id = line.substr(0, id_end) };
        std::stringstream ss(line.substr(id_end + 1, line.length() - (id_end + 2)));
        while (std::getline(ss, line, ','))
        {
            rule.conditions.push_back(line);
        }
        rules.push_back(rule);
    }
    while (std::getline(file, line))
    {
        Part new_part;
        std::stringstream ss(line.substr(1, line.length() - 2));
        int part_idx = 0;
        while (std::getline(ss, line, ',') && part_idx < (int)Part::PartRatingType::NUM_ENTRIES)
        {
            new_part.entries[part_idx++] = std::stoi(line.substr(2));
        }
        parts.push_back(new_part);
    }

    std::cout << "Accepted part total: " << solve_part_list(rules, parts) << std::endl;
    std::cout << "Possible Accepted parts: " << solve_possible_parts(rules) << std::endl;
}
