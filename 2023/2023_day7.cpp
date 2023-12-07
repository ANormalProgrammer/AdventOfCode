#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <map>
#include <sstream>

class Card_hand
{
private:
    std::string m_hand;
    long long m_bid_value;
public:
    Card_hand(std::string hand, long long bid_value)  :
    m_hand {hand}, m_bid_value {bid_value} {};

    std::string get_hand() const {return m_hand;}
    long long get_bid_value() const {return m_bid_value;}
};

enum Strength_type
{
    high_card,
    one_pair,
    two_pair,
    three_of_a_kind,
    full_house,
    four_of_a_kind,
    five_of_a_kind
};

bool is_find(std::vector<int> vec, int target)
{
    return std::find(vec.begin(), vec.end(), target) != vec.end();
}

namespace part_1
{
    std::map<char, int> convert_to_relative_strength
    {
        {'2', 1},
        {'3', 2},
        {'4', 3},
        {'5', 4},
        {'6', 5},
        {'7', 6},
        {'8', 7},
        {'9', 8},
        {'T', 9},
        {'J', 10},
        {'Q', 11},
        {'K', 12},
        {'A', 13}
    };
    Strength_type get_strength_type(std::string hand)
    {
        std::vector<int> occurrence;

        std::map<char, int> count_occurrence;
        for(auto c : hand)
        {
            ++count_occurrence[c];
        }
        for(auto p : count_occurrence)
            occurrence.push_back(p.second);
        if (is_find(occurrence, 5))
        {
            return five_of_a_kind;
        }
        else if (is_find(occurrence, 4))
        {
            return four_of_a_kind;
        }
        else if (is_find(occurrence, 3) && is_find(occurrence, 2))
        {
            return full_house;
        }
        else if (is_find(occurrence, 3))
        {
            return three_of_a_kind;
        }
        else if(std::count(occurrence.begin(), occurrence.end(), 2) == 2)
        {
            return two_pair;
        }
        else if(is_find(occurrence, 2))
        {
            return one_pair;
        }
        else
        {
            return high_card;
        }
    }
    bool compare (const Card_hand& c1, const Card_hand& c2)
    {
        std::string c1_hand = c1.get_hand();
        std::string c2_hand = c2.get_hand();

        if(part_1::get_strength_type(c1_hand) != part_1::get_strength_type(c2_hand))
            return part_1::get_strength_type(c1_hand) < part_1::get_strength_type(c2_hand);
        else
        {
            for(int i = 0; i < 5; ++i)
            {
                if(c1_hand[i] != c2_hand[i])
                    return part_1::convert_to_relative_strength[c1_hand[i]] < part_1::convert_to_relative_strength[c2_hand[i]];
            }
            return false;
        }
    }
}

namespace part_2
{
    std::string all_card_face = "23456789TQKA";
    std::map<char, int> convert_to_relative_strength
    {
        {'J', 1},
        {'2', 2},
        {'3', 3},
        {'4', 4},
        {'5', 5},
        {'6', 6},
        {'7', 7},
        {'8', 8},
        {'9', 9},
        {'T', 10},
        {'Q', 11},
        {'K', 12},
        {'A', 13}
    };
    Strength_type get_strength_type(std::string hand)
    {
        Strength_type max_hand_strength = high_card;
        for(auto face : all_card_face)
        {
            std::string possible_hand = hand;
            std::replace(possible_hand.begin(), possible_hand.end(), 'J', face);

            Strength_type hand_strength;

            std::vector<int> occurrence;

            std::map<char, int> count_occurrence;
            for(auto c : possible_hand)
            {
                ++count_occurrence[c];
            }
            for(auto p : count_occurrence)
                occurrence.push_back(p.second);

            if (is_find(occurrence, 5))
            {
                 hand_strength = five_of_a_kind;
            }
            else if (is_find(occurrence, 4))
            {
                hand_strength = four_of_a_kind;
            }
            else if (is_find(occurrence, 3) && is_find(occurrence, 2))
            {
                hand_strength = full_house;
            }
            else if (is_find(occurrence, 3))
            {
                hand_strength = three_of_a_kind;
            }
            else if(std::count(occurrence.begin(), occurrence.end(), 2) == 2)
            {
                hand_strength = two_pair;
            }
            else if(is_find(occurrence, 2))
            {
                hand_strength = one_pair;
            }
            else
            {
                hand_strength = high_card;
            }
            max_hand_strength = std::max(max_hand_strength, hand_strength);
        }
        return max_hand_strength;
    }

    bool compare (const Card_hand& c1, const Card_hand& c2)
    {
        std::string c1_hand = c1.get_hand();
        std::string c2_hand = c2.get_hand();

        if(part_2::get_strength_type(c1_hand) != part_2::get_strength_type(c2_hand))
            return part_2::get_strength_type(c1_hand) < part_2::get_strength_type(c2_hand);
        else
        {
            for(int i = 0; i < 5; ++i)
            {
                if(c1_hand[i] != c2_hand[i])
                    return part_2::convert_to_relative_strength[c1_hand[i]] < part_2::convert_to_relative_strength[c2_hand[i]];
            }
            return false;
        }
    }
}


std::vector<std::string> process_input()
{
    std::string s;
    std::vector<std::string> input;
    while(std::getline(std::cin, s))
    {
        input.push_back(s);
    }
    return input;
}

long long part1(std::vector<std::string>& input)
{
    std::vector<Card_hand> cards_hand;

    for(const std::string& card_hand : input)
    {
        std::stringstream ss (card_hand);

        std::string hand;
        ss >> hand;
        std::string bid_str;
        ss >> bid_str;
        long long bid = std::stoll(bid_str);
        cards_hand.push_back({hand, bid});
    }
    std::sort(cards_hand.begin(), cards_hand.end(), part_1::compare);

    long long total_winnings = 0;
    for(int i = 0; i < cards_hand.size(); ++i)
    {
        total_winnings += (i + 1) * cards_hand[i].get_bid_value();
    }

    return total_winnings;
}

long long part2(std::vector<std::string>& input)
{
    std::vector<Card_hand> cards_hand;

    for(const std::string& card_hand : input)
    {
        std::stringstream ss (card_hand);

        std::string hand;
        ss >> hand;
        std::string bid_str;
        ss >> bid_str;
        long long bid = std::stoll(bid_str);
        cards_hand.push_back({hand, bid});
    }
    std::sort(cards_hand.begin(), cards_hand.end(), part_2::compare);

    long long total_winnings = 0;
    for(int i = 0; i < cards_hand.size(); ++i)
    {
        total_winnings += (i + 1) * cards_hand[i].get_bid_value();
    }

    return total_winnings;
}
int main()
{
    //std::freopen("day7inp.txt", "r", stdin);
    //std::freopen("day7out.txt", "w", stdout);

    std::vector<std::string> input = process_input();

    std::cout << "The solution for part 1 is: " << part1(input) <<'\n';
    std::cout << "The solution for part 2 is: " << part2(input) <<'\n';

}
