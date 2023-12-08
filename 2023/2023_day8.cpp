#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <map>
#include <sstream>
#include <utility>

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
long long __lcm(long long a, long long b)
{
    return a / std::__gcd(a, b) * b;
}
long long part1(const std::vector<std::string>& input)
{
    std::string path_instructions = input[0];

    std::map<std::string, std::pair<std::string, std::string>> network;

    for(int index_of_input = 2; index_of_input < input.size(); ++index_of_input)
    {
        std::stringstream ss (input[index_of_input]);
        std::string node, equal_sign, left, right;

        ss >> node >> equal_sign >> left >> right;

        left.erase(left.begin());
        left.erase(left.end() - 1);
        right.erase(right.end() - 1);

        network[node] = {left, right};
    }

    std::string current_node = "AAA";
    long long steps = 0;
    int instruction_index = 0;

    while(current_node != "ZZZ")
    {
        ++steps;
        char direction = path_instructions[instruction_index];
        if(direction == 'L')
            current_node = network[current_node].first;
        else if(direction == 'R')
            current_node = network[current_node].second;

        ++instruction_index;
        if(instruction_index >= path_instructions.size())
            instruction_index = 0;
    }

    return steps;
}

long long part2(const std::vector<std::string>& input)
{
    std::string path_instructions = input[0];

    std::map<std::string, std::pair<std::string, std::string>> network;

    for(int index_of_input = 2; index_of_input < input.size(); ++index_of_input)
    {
        std::stringstream ss (input[index_of_input]);
        std::string node, equal_sign, left, right;

        ss >> node >> equal_sign >> left >> right;

        left.erase(left.begin());
        left.erase(left.end() - 1);
        right.erase(right.end() - 1);

        network[node] = {left, right};
    }

    std::vector<std::string> starting_node;
    for(const auto &node : network)
    {
        if(node.first[node.first.size() - 1] == 'A')
            starting_node.push_back(node.first);
    }
    long long steps_simultaneously = 1;
    for(const auto &node : starting_node)
    {
        std::string current_node = node;
        long long steps = 0;
        int instruction_index = 0;

        while(current_node[current_node.size() - 1] != 'Z')
        {
            ++steps;
            char direction = path_instructions[instruction_index];
            if(direction == 'L')
                current_node = network[current_node].first;
            else if(direction == 'R')
                current_node = network[current_node].second;

            ++instruction_index;
            if(instruction_index >= path_instructions.size())
                instruction_index = 0;
        }

        steps_simultaneously = __lcm(steps_simultaneously, steps);
    }
    return steps_simultaneously;
}


int main()
{
    //std::freopen("day8inp.txt", "r", stdin);
    //std::freopen("day8out.txt", "w", stdout);

    std::vector<std::string> input = process_input();

    std::cout << "The solution for part 1 is: " << part1(input) <<'\n';
    std::cout << "The solution for part 2 is: " << part2(input) <<'\n';
}
