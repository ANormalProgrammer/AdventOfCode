#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <map>

std::pair<std::vector<int>, std::vector<int>> processInput()
{
    std::pair<std::vector<int>, std::vector<int>> input;
    int first_number, second_number;

    while(std::cin >> first_number >> second_number)
    {
        input.first.push_back(first_number);
        input.second.push_back(second_number);
    }
    return input;
}

long long part1(std::pair<std::vector<int>, std::vector<int>>  input)
{
    std::sort(input.first.begin(), input.first.end());
    std::sort(input.second.begin(), input.second.end());

    long long total_distance = 0;

    for(int i = 0; i < input.first.size(); ++i)
    {
        total_distance += std::abs(input.first[i] - input.second[i]);
    }
    return total_distance;
}
long long part2(std::pair<std::vector<int>, std::vector<int>>  input)
{
    std::map<int, int> number_of_appearance_in_right_list;
    for(int number : input.second)
    {
        ++number_of_appearance_in_right_list[number];
    }
    long long similarity_score = 0;
    for(int number : input.first)
    {
        similarity_score += number * number_of_appearance_in_right_list[number];
    }
    return similarity_score;
}

int main(int argc, char** argv)
{
    if(argc == 1)
        std::freopen("day1inp.txt", "r", stdin);
    else
        std::freopen(argv[1], "r", stdin);

    std::pair<std::vector<int>, std::vector<int>>  input = processInput();
    std::cout << "The solution to part 1 is: " << part1(input) << '\n';
    std::cout << "The solution to part 2 is: " << part2(input) << '\n';
}
