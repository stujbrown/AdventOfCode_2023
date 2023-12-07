#include "aoc_days.hpp"
#include <array>
#include <numeric>
#include <map>

struct Hand
{
    std::array<int, 5> value_indices;
    int bid;
    int hand_score;
};

void aoc::day7()
{
    std::ifstream file("inputs/day7.txt");
    std::string token;
    
    std::vector<Hand> hands;
    
    std::map<char, int> indices { {'2', 0}, {'3', 1}, {'4', 2}, {'5', 3}, {'6', 4}, {'7', 5}, {'8', 6}, {'9', 7}, {'T', 8}, {'J', 9}, {'Q', 10}, {'K', 11}, {'A', 12} };
    while (file >> token)
    {
        std::array<int, 13> value_counts;
        value_counts.fill(0);
        
        Hand hand;
        for (size_t i = 0; i < token.length(); ++i)
        {
            hand.value_indices[i] = indices[token[i]];
            ++value_counts[indices[token[i]]];
        }
        
        // 4-bits to represent 13 values, so 20 bits to represent the top per-card score
        static const int max_hand_score = 0b11111111111111111111;
        int score = 0, total_rating = 0;
        for (size_t i = 0; i < 5; ++i)
            score |= (hand.value_indices[i] + 1) << (4 * (4 - i)); // Pack all card values left-first
        
        if (std::find(value_counts.begin(), value_counts.end(), 5) != value_counts.end())
        {
            total_rating = (max_hand_score * 6) + score;
        }
        else if (std::find(value_counts.begin(), value_counts.end(), 4) != value_counts.end())
        {
            total_rating = (max_hand_score * 5) + score;
        }
        else if (std::find(value_counts.begin(), value_counts.end(), 3) != value_counts.end() &&
                 std::find(value_counts.begin(), value_counts.end(), 2) != value_counts.end())
        {
            total_rating = (max_hand_score * 4) + score;
        }
        else if (std::find(value_counts.begin(), value_counts.end(), 3) != value_counts.end())
        {
            total_rating = (max_hand_score * 3) + score;
        }
        else
        {
            const size_t num_pairs = std::count(value_counts.begin(), value_counts.end(), 2);
            if (num_pairs == 2)
            {
                total_rating = (max_hand_score * 2) + score;
            }
            else if (num_pairs == 1)
            {
                total_rating = max_hand_score + score;
            }
            else
            {
                total_rating = score;
            }
        }
        
        hand.hand_score = total_rating;
        
        file >> token;
        hand.bid = std::stoi(token);
        hands.emplace_back(std::move(hand));
    }
    
    std::sort(hands.begin(), hands.end(), [](const Hand& lhs, const Hand& rhs) { return lhs.hand_score < rhs.hand_score; });
    
    int winnings = 0;
    for (size_t i = 0; i < hands.size(); ++i)
    {
        winnings += hands[i].bid * (i + 1);
    }
    std::cout << "Total winnings: " << winnings << std::endl;
}
