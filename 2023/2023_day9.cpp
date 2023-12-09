#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <algorithm>
#include <limits>

std::vector<std::string> processInput()
{
    std::string s;
    std::vector<std::string> input;
    while(std::getline(std::cin, s))
    {
        input.push_back(s);
    }
    return input;
}

bool is_number(std::string str)
{
    for(auto c : str)
    {
        if(c == '-') continue;
        if (c <'0' || c > '9')
        {
            return false;
        }
    }
    return true;
}
std::vector<long long> get_int (std::string line)
{
    std::vector<long long> int_list;
    std::stringstream ss (line);
    std::string token;
    while(ss >> token)
    {
        if(!token.empty() && is_number(token))
        {
            int_list.push_back(std::stoll(token));
        }
    }
    return int_list;
}
long long part1(const std::vector<std::string>& input)
{
    long long next_value = 0;

    for(std::string single_value : input)
    {
        if(single_value.empty()) continue;
        std::vector<std::vector<long long>> extrapolate;
        std::vector<long long> history = get_int(single_value);
        extrapolate.push_back(history);

        long long extrapolate_idx = 0;
        while(true)
        {

            bool is_only_zero = true;
            std::vector<long long> sequence;
            int extrapolate_size = extrapolate[extrapolate_idx].size();
            for(int i = 1; i < extrapolate_size; ++i)
            {
                long long new_number_in_sequence = extrapolate[extrapolate_idx][i] - extrapolate[extrapolate_idx][i - 1];
                sequence.push_back(new_number_in_sequence);
                if(new_number_in_sequence != 0) is_only_zero = false;
            }
            extrapolate.push_back(sequence);

            if(is_only_zero) break;

            ++extrapolate_idx;
        }
        for(const auto& history : extrapolate)
        {
            next_value += history[history.size() - 1];
        }
    }
    return next_value;
}
long long part2(const std::vector<std::string>& input)
{
    long long next_value = 0;

    for(std::string single_value : input)
    {
        long long extrapolated_value = 0;
        if(single_value.empty()) continue;
        std::vector<std::vector<long long>> extrapolate;
        std::vector<long long> history = get_int(single_value);
        extrapolate.push_back(history);
        long long extrapolate_idx = 0;
        while(true)
        {

            bool is_only_zero = true;
            std::vector<long long> sequence;
            int extrapolate_size = extrapolate[extrapolate_idx].size();
            for(int i = 1; i < extrapolate_size; ++i)
            {
                long long new_number_in_sequence = extrapolate[extrapolate_idx][i] - extrapolate[extrapolate_idx][i - 1];
                sequence.push_back(new_number_in_sequence);
                //std::cout << new_number_in_sequence << ' ';
                if(new_number_in_sequence != 0) is_only_zero = false;
            }
            extrapolate.push_back(sequence);

            if(is_only_zero) break;

            ++extrapolate_idx;
        }
        std::reverse(extrapolate.begin(), extrapolate.end());

        for(auto history : extrapolate)
        {
            extrapolated_value = history[0] - extrapolated_value;
        }
        next_value += extrapolated_value;
    }
    return next_value;
}
int main()
{
    //std::freopen("day9inp.txt", "r", stdin);
    //std::freopen("day9out.txt", "w", stdout);

    std::vector<std::string> input = processInput();

    std::cout << "The solution for part 1 is: " << part1(input) <<'\n';
    std::cout << "The solution for part 2 is: " << part2(input) <<'\n';
}

