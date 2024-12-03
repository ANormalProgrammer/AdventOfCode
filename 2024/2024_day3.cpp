#include <iostream>
#include <vector>
#include <string>
#include <regex>

std::vector<std::string> regex_search(std::regex regular_expression, std::string line)
{
    std::vector<std::string> matches;
    auto regex_begin = std::sregex_iterator(line.begin(), line.end(), regular_expression);
    auto regex_end = std::sregex_iterator();

    for (std::sregex_iterator i = regex_begin; i != regex_end; ++i)
    {
        std::smatch match = *i;
        matches.push_back(match.str()) ;
    }
    return matches;
}

long long find_mutiply(std::string mul_operator)
{
    long long mutiply = 1;
    mul_operator = mul_operator.substr(4); // remove the "mul(" part from the string

    std::istringstream ss (mul_operator);
    std::string number_str;
    while(std::getline(ss, number_str, ','))
    {
        mutiply *= std::stol(number_str);
    }

    return mutiply;
}

std::vector<std::string> processInput()
{
    std::vector<std::string> input;
    std::string line;
    while(std::cin >> line)
    {
        input.push_back(line);
    }
    std::cin.ignore(256, '\n');
    return input;
}

long long part1(const std::vector<std::string> &input)
{
    std::regex mul_regex ("mul\\(\\d+,\\d+\\)");
    long long sum = 0;
    for(const std::string& line : input)
    {
        std::vector<std::string> mul_operators = regex_search(mul_regex, line);
        for(std::string mul_operator : mul_operators)
            sum += find_mutiply(mul_operator);
    }
    return sum;
}
long long part2(std::vector<std::string> input)
{
    std::regex valid_space_regex("do[^n't].*?don't");
    std::regex mul_regex ("mul\\(\\d+,\\d+\\)");
    std::string concatenation;
    for(const std::string& line : input)
    {
        concatenation += line;
    }
    concatenation = "do" + concatenation + "don't";

    long long sum = 0;
    std::vector<std::string> valid_spaces = regex_search(valid_space_regex, concatenation);
    for(const std::string& valid_space : valid_spaces)
    {
        std::vector<std::string> mul_operators = regex_search(mul_regex, valid_space);
        for(std::string mul_operator : mul_operators)
            sum += find_mutiply(mul_operator);
    }

    return sum;
}
int main(int argc, char** argv)
{
    if(argc == 1)
        std::freopen("day3inp.txt", "r", stdin);
    else
        std::freopen(argv[1], "r", stdin);

    std::vector<std::string> input = processInput();
    std::cout << "The solution to part 1 is: " << part1(input) << '\n';
    std::cout << "The solution to part 2 is: " << part2(input) << '\n';
}
