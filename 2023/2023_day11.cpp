#include <iostream>
#include <vector>
#include <string>

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

bool checkrow(std::vector<std::string> space, long long row_num)
{
    for(auto c : space[row_num])
        if(c == '#')
            return false;

    return true;
}

bool checkcol(std::vector<std::string> space, long long col_num)
{
    for(auto str : space)
        if(str[col_num] == '#')
            return false;

    return true;
}

long long general_solution(std::vector<std::string> space, long long expansion_rate)
{
    std::vector<long long> empty_row, empty_col;
    long long num_row = space.size();
    long long num_col = space[0].size();

    // precompute start of the empty rows and columns;
    for(long long i = 0; i < num_row; ++i)
    {
        if(checkrow(space, i))
            empty_row.push_back(i + (empty_row.size() * (expansion_rate - 1)));
    }
    for(long long i = 0; i < num_col; ++i)
    {
        if(checkcol(space, i))
            empty_col.push_back(i + (empty_col.size() * (expansion_rate - 1)));
    }

    std::vector<std::pair<long long, long long>> hash_cords;
    for(long long i = 0; i < num_row; ++i)
    {
        for(long long j = 0; j < num_col; ++j)
        {
            if(space[i][j] == '#')
                hash_cords.push_back({i, j});
        }
    }
    // if the hash comes after the empty row/col, then we update it.

    for(auto em_row : empty_row)
    {
        for(auto &p : hash_cords)
        {
            if(p.first >= em_row)
                p.first += expansion_rate - 1;
        }
    }
    for(auto em_col : empty_col)
    {
        for(auto &p : hash_cords)
        {
            if(p.second >= em_col)
            {
                p.second += expansion_rate - 1;
            }
        }
    }
    //calculate the sum distance
    long long ans = 0;
    for(long long i = 0; i < hash_cords.size(); ++i)
    {
        for(long long j = i + 1; j < hash_cords.size(); ++j)
        {
            ans += std::abs(hash_cords[i].first - hash_cords[j].first) + std::abs(hash_cords[i].second - hash_cords[j].second);
        }
    }

    return ans;
}

long long part1(std::vector<std::string> space)
{
    return general_solution(space, 2);
}

long long part2(std::vector<std::string> space)
{
    return general_solution(space, 1000000);
}


int main()
{

    std::freopen("day11inp.txt", "r", stdin);
    std::freopen("day11out.txt", "w", stdout);

    std::vector<std::string> input = processInput();
    std::cout << "The solution for part 1 is: "  << part1(input) <<'\n';
    std::cout << "The solution for part 2 is: "  << part2(input) <<'\n';


}
