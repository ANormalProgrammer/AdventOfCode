#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

struct Equation
{
    long long test_value;
    std::vector<long long> rhs;
};

std::vector<Equation> processInput()
{
    std::vector<Equation> input;

    std::string line;
    while(std::getline(std::cin, line))
    {
        Equation equation;
        if(!line.empty())
        {
            std::stringstream ss(line);
            std::string number_str;
            while(ss >> number_str)
            {
                if(number_str.find(':') != std::string::npos)
                {
                    equation.test_value = std::stoll(number_str.substr(0, number_str.size() - 1));
                }
                else
                {
                    equation.rhs.push_back(std::stoll(number_str));
                }
            }
            input.push_back(equation);
        }
    }
    return input;
}
long long addition_operator(long long a, long long b)
{
    return a + b;
}
long long mutiply_operator(long long a, long long b)
{
    return a * b;
}

long long concenetation_operator(long long a, long long b)
{
    std::string a_str = std::to_string(a);
    std::string b_str = std::to_string(b);
    std::string result = a_str + b_str;
    return std::stoll(result);

}

bool can_euqation_be_correct(Equation equation, long long result, int index, std::string mode)
{

    if(result > equation.test_value) return false;

    if(index >= equation.rhs.size())
    {
        if(result == equation.test_value) return true;
        else return false;
    }
    long long addiction = addition_operator(result, equation.rhs[index]);
    long long mutiply = mutiply_operator(result, equation.rhs[index]);
    long long concat = concenetation_operator(result, equation.rhs[index]);

    if(mode == "part1")
    {
        return can_euqation_be_correct(equation, addiction, index + 1, mode)
            ||     can_euqation_be_correct(equation, mutiply, index + 1, mode);
    }
    else
    {
        return can_euqation_be_correct(equation, addiction, index + 1, mode)
        ||     can_euqation_be_correct(equation, mutiply, index + 1, mode)
        ||     can_euqation_be_correct(equation, concat, index + 1, mode);
    }
}

long long part1(const std::vector<Equation> input)
{
    long long answer = 0;
    for(auto equation : input)
    {
        if(can_euqation_be_correct(equation, equation.rhs[0], 1, "part1"))
        {
            answer += equation.test_value;
        }
    }
    return answer;
}
long long part2(const std::vector<Equation> input)
{
    long long answer = 0;
    for(auto equation : input)
    {
        if(can_euqation_be_correct(equation, equation.rhs[0], 1, "part2"))
        {
            answer += equation.test_value;
        }
    }
    return answer;
}


int main(int argc, char** argv)
{
    if(argc == 1)
        std::freopen("day7inp.txt", "r", stdin);
    else
        std::freopen(argv[1], "r", stdin);

    std::vector<Equation> input = processInput();

    std::cout << "The solution to part 1 is: " << part1(input) << '\n';
    std::cout << "The solution to part 2 is: " << part2(input) << '\n';
}



