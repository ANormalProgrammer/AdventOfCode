#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdio>
#include <array>
#include <algorithm>

std::vector<std::string> processInput()
{
    std::string s;
    std::vector<std::string> input;
    while(std::cin >> s)
    {
        input.push_back(s);
    }
    return input;
}

long long part1(std::vector<std::string> input)
{
    long long sum = -0;
    for(const auto& str : input)
    {
        bool is_first_digit = true;
        std::string calibration_value;
        char digit{};

        for(const auto &c : str)
        {
            if(c >= '0' && c <= '9')
            {
                digit = c;
                if(is_first_digit)
                {
                    calibration_value += digit;
                    is_first_digit = false;
                }
            }
        }
        calibration_value += digit;

        sum += std::stol(calibration_value);
    }
    return sum;
}

long long part2(std::vector<std::string> input)
{
    std::array<std::string, 9> number_as_string {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    long long sum = 0;
    for(const auto& str : input)
    {
        bool is_first_digit = true;
        bool is_real_digit = false;

        std::string calibration_value;
        std::string number_in_string;

        int first_index = 0;

        for(int i = 0; i < str.size(); ++i)
        {
            if(str[i] >= '0' && str[i] <= '9')
            {
                number_in_string = str[i];
                first_index = i;
                is_real_digit = true;
            }
            else
            {

                for(int j = first_index; j <= i; ++j)
                {
                    std::string possible_number = str.substr(j, i - j + 1);
                    auto idx = std::find(std::begin(number_as_string), std::end(number_as_string), possible_number);
                    if(idx != std::end(number_as_string))
                    {

                        number_in_string = std::to_string(std::distance(std::begin(number_as_string), idx + 1));

                        first_index = i;
                        is_real_digit = true;

                        break;
                    }
                }
            }
            if(is_first_digit && is_real_digit)
            {
                calibration_value += number_in_string;
                is_first_digit = false;
                is_real_digit = false;
            }
        }
        calibration_value += number_in_string;
        sum += std::stol(calibration_value);
    }
    return sum;
}

int main()
{
    //std::freopen("day1inp.txt", "r", stdin);
    //std::freopen("day1out.txt", "w", stdout);

    std::vector<std::string> input = processInput();

    std::cout << "The solution for part 1 is: " << part1(input) <<'\n';
    std::cout << "The solution for part 2 is: " << part2(input) <<'\n';
}
