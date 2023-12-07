#include "aoc_days.hpp"
#include <array>
#include <numeric>
#include <map>

struct Hand
{
    long bid;
    long hand_score;
};

long grade_hand(const std::map<char, long>& score_indices, const std::string& hand_str, bool use_joker)
{
    std::array<long, 13> value_counts;
    value_counts.fill(0);
    
    for (size_t i = 0; i < hand_str.length(); ++i)
    {
        if (hand_str[i] != 'J')
            ++value_counts[score_indices.find(hand_str[i])->second];
    }
    std::sort(value_counts.begin(), value_counts.end(), std::greater_equal<long>());
    
    // 4-bits to represent 13 values, so 20 bits to represent the top per-card score
    static const long max_hand_score = 0b11111111111111111111;
    long score = 0;
    for (size_t i = 0; i < 5; ++i)
        score |= (score_indices.find(hand_str[i])->second + 1) << (4 * (4 - i));
    
    const size_t joker_count = use_joker ? std::count(hand_str.begin(), hand_str.end(), 'J') : 0;
    if (value_counts[0] >= 5 - joker_count)
        return (max_hand_score * 6) + score;
    
    if (value_counts[0] >= 4 - joker_count)
        return (max_hand_score * 5) + score;
    
    if (value_counts[0] + value_counts[1] >= 5 - joker_count)
        return (max_hand_score * 4) + score;
    
    if (value_counts[0] >= 3 - joker_count)
        return (max_hand_score * 3) + score;
    
    if (value_counts[0] + value_counts[1] >= 4 - joker_count)
        return (max_hand_score * 2) + score;
    
    if (value_counts[0] >= 2 - joker_count)
        return max_hand_score + score;
    
    return score;
}

long solve(bool use_joker)
{
    std::ifstream file("inputs/day7.txt");
    std::string hand_token, bid_token;
    std::vector<Hand> hands;
    
    const std::map<char, long> basic_indices { {'2', 0}, {'3', 1}, {'4', 2}, {'5', 3}, {'6', 4}, {'7', 5}, {'8', 6}, {'9', 7}, {'T', 8}, {'J', 9}, {'Q', 10}, {'K', 11}, {'A', 12} };
    const std::map<char, long> joker_indices { {'J', 0}, {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4}, {'6', 5}, {'7', 6}, {'8', 7}, {'9', 8}, {'T', 9}, {'Q', 10}, {'K', 11}, {'A', 12} };
    const std::map<char, long>& score_indices = use_joker ? joker_indices : basic_indices;
    
    while (file >> hand_token && file >> bid_token)
    {
        hands.emplace_back(std::move(Hand
        {
            .hand_score = grade_hand(score_indices, hand_token, use_joker),
            .bid = std::stoi(bid_token)
        }));
        
    }
    
    std::sort(hands.begin(), hands.end(), [](const Hand& lhs, const Hand& rhs) { return lhs.hand_score < rhs.hand_score; });
    
    long winnings = 0;
    for (size_t i = 0; i < hands.size(); ++i)
        winnings += hands[i].bid * (i + 1);
    return winnings;
}

void aoc::day7()
{
    const long winnings = solve(false);
    const long joker_winnings = solve(true);
    std::cout << "Total winnings: " << winnings << std::endl;
    std::cout << "Total winnings with joker: " << joker_winnings << std::endl;
}
