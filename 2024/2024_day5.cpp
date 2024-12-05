#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

struct Input
{
    std::unordered_map<int, std::unordered_set<int>> page_ordering_rules;
    std::vector<std::vector<int>> updates;
};

Input processInput()
{
    std::unordered_map<int, std::unordered_set<int>> page_ordering_rules;
    std::vector<std::vector<int>> updates;
    std::string input;
    while(std::cin >> input)
    {
        if(input.find('|') != std::string::npos)
        {
            int first_number = std::stoi(input.substr(0, 2));
            int second_number = std::stoi(input.substr(3, 2));
            page_ordering_rules[first_number].insert(second_number);
        }
        else
        {
            std::istringstream ss (input);
            std::string number_str;
            std::vector<int> pages;
            while(std::getline(ss, number_str, ','))
            {
                pages.push_back(std::stol(number_str));
            }
            updates.push_back(pages);
        }
    }
    return {page_ordering_rules, updates};
}

// return false if the update is correct,
// else return the index of the latter element when it fails

int is_update_false( std::unordered_map<int, std::unordered_set<int>> &page_ordering_rules,
                            std::vector<int>& update)
{
    for(int i = 0; i + 1 < update.size(); ++i)
    {
        if(page_ordering_rules[update[i + 1]].contains(update[i]))
            return i + 1;
    }
    return false;
}

long long part1(Input& input)
{
    long long calculate_sum_updates = 0;
    for(auto update : input.updates)
    {
        if(!is_update_false(input.page_ordering_rules, update))
            calculate_sum_updates += update[update.size() / 2];
    }
    return calculate_sum_updates;
}
long long part2(Input& input)
{
    long long calculate_sum_updates = 0;
    for(auto update : input.updates)
    {
        if(is_update_false(input.page_ordering_rules, update))
        {
            while(int i = is_update_false(input.page_ordering_rules, update))
            {
                std::swap(update[i], update[i - 1]);
            }
            calculate_sum_updates += update[update.size() / 2];
        }
    }
    return calculate_sum_updates;
}
int main(int argc, char** argv)
{
    if(argc == 1)
        std::freopen("day5inp.txt", "r", stdin);
    else
        std::freopen(argv[1], "r", stdin);

    Input input = processInput();

    std::cout << "The solution to part 1 is: " << part1(input) << '\n';
    std::cout << "The solution to part 2 is: " << part2(input) << '\n';
}
