#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <cmath>

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
long long get_int_skip_space(std::string line)
{
    std::string number;
    std::stringstream ss (line);
    std::string token;
    while(ss >> token)
    {
        if(!token.empty() && is_number(token))
        {
            number += token;
        }
    }
    return stoll(number);
}

bool is_double_int(double d)
{
    long long i = (int)d;
    return i == d;
}
long long part1(const std::vector<std::string>& input)
{
    long long margin_of_error = 1;
    std::vector<long long> times = get_int(input[0]);
    std::vector<long long> distances = get_int(input[1]);

    for(int i = 0; i < times.size(); ++i)
    {
        long long time = times[i];
        long long distance = distances[i];

        double delta = std::sqrt(time * time - 4 * distance);

        double first_root = (time - delta) / 2;
        double second_root = (time + delta) / 2;

        if(is_double_int(first_root)) ++ first_root;
        if(is_double_int(second_root)) --second_root;
        long long ways_of_winning = std::floor(second_root) - std::ceil(first_root) + 1;

        margin_of_error *= ways_of_winning;
    }
    return margin_of_error;
}
long long part2(const std::vector<std::string>& input)
{
    long long margin_of_error = 1;

    long long time = get_int_skip_space(input[0]);
    long long distance = get_int_skip_space(input[1]);

    double delta = std::sqrt(time * time - 4 * distance);

    double first_root = (time - delta) / 2;
    double second_root = (time + delta) / 2;

    if(is_double_int(first_root)) ++ first_root;
    if(is_double_int(second_root)) --second_root;
    long long ways_of_winning = std::floor(second_root) - std::ceil(first_root) + 1;

    margin_of_error *= ways_of_winning;
    return margin_of_error;
}
int main()
{
    std::freopen("day6inp.txt", "r", stdin);
    //std::freopen("day6out.txt", "w", stdout);

    std::vector<std::string> input = processInput();

    std::cout << part2(input) <<'\n';
}
