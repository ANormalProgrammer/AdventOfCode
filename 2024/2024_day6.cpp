#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

struct Position
{
    int x;
    int y;
};
bool operator<(const Position& l, const Position& r) {
     return (l.x <r.x || (l.x==r.x && l.y<r.y));
}

enum class Directions
{
    up,
    right,
    down,
    left
};



std::vector<std::string> processInput()
{
    std::vector<std::string> input;
    std::string line;
    while(std::cin >> line)
    {
        if(!line.empty())
            input.push_back(line);
    }
    return input;
}

void guard_action(long long &answer, const std::vector<std::string>& input,std::vector<std::vector<bool>>& is_visited,
                  Position position, Directions direction)
{
    if (!is_visited[position.x][position.y])
    {
        ++answer;
        is_visited[position.x][position.y] = true;
    }

    Position new_position;
    Directions new_direction;

    switch(direction)
    {
    case Directions::up:
        new_direction = Directions::right;
        new_position = {position.x - 1, position.y};
        break;
    case Directions::right:
        new_direction = Directions::down;
        new_position = {position.x, position.y + 1};
        break;
    case Directions::down:
        new_direction = Directions::left;
        new_position = {position.x + 1, position.y};
        break;
    case Directions::left:
        new_direction = Directions::up;
        new_position = {position.x, position.y - 1};
        break;
    }
    if(new_position.x < 0 || new_position.x >= input.size()) return;
    if(new_position.y < 0 || new_position.y >= input[0].size()) return;

    if(input[new_position.x][new_position.y] == '.' || input[new_position.x][new_position.y] == '^')
    {
        guard_action(answer, input, is_visited, new_position, direction);
    }
    else if(input[new_position.x][new_position.y] == '#')
    {
        guard_action(answer, input, is_visited, position, new_direction);
    }
    return;
}
bool is_in_loop(const std::vector<std::string>& input, std::map<Position, std::set<Directions>>& all_state,
                  Position position, Directions direction)
{
    if(all_state[position].contains(direction))
    {
        return true;
    }
    else
    {
        all_state[position].insert(direction);
    }
    Position new_position;
    Directions new_direction;

    switch(direction)
    {
    case Directions::up:
        new_direction = Directions::right;
        new_position = {position.x - 1, position.y};
        break;
    case Directions::right:
        new_direction = Directions::down;
        new_position = {position.x, position.y + 1};
        break;
    case Directions::down:
        new_direction = Directions::left;
        new_position = {position.x + 1, position.y};
        break;
    case Directions::left:
        new_direction = Directions::up;
        new_position = {position.x, position.y - 1};
        break;
    }
    if(new_position.x < 0 || new_position.x >= input.size()) return false;
    if(new_position.y < 0 || new_position.y >= input[0].size()) return false;

    if(input[new_position.x][new_position.y] == '.' || input[new_position.x][new_position.y] == '^')
    {
        return is_in_loop(input, all_state, new_position, direction);
    }
    else if(input[new_position.x][new_position.y] == '#')
    {
        return is_in_loop(input, all_state, position, new_direction);
    }
}

Position search_for_starting_position(const std::vector<std::string>& input)
{
    for(int x = 0; x < input.size(); ++x)
    {
        for(int y = 0; y < input[0].size(); ++y)
        {
            if(input[x][y] == '^')
                return {x, y};
        }
    }
}
long long part1(const std::vector<std::string>& input)
{
    std::vector<std::vector<bool>> is_visited (input.size(), std::vector<bool>(input[0].size()));
    Position start_pos = search_for_starting_position(input);
    long long answer = 0;
    guard_action(answer, input, is_visited, start_pos, Directions::up);
    return answer;
}

long long part2(std::vector<std::string>& input)
{
    Position start_pos = search_for_starting_position(input);

    long long answer = 0;

    for(int x = 0; x < input.size(); ++x)
    {
        for(int y = 0; y < input[0].size(); ++y)
        {
            if(input[x][y] == '.')
            {
                //std::cout << x << ' ' << y << '\n';
                input[x][y] = '#';

                std::map<Position, std::set<Directions>> all_state;
                if(is_in_loop(input, all_state, start_pos, Directions::up))
                    ++answer;

                input[x][y] = '.';
            }
        }
    }
    return answer;
}
int main(int argc, char** argv)
{
    if(argc == 1)
        std::freopen("day6inp.txt", "r", stdin);
    else
        std::freopen(argv[1], "r", stdin);

    std::vector<std::string>  input = processInput();
    std::cout << "The solution to part 1 is: " << part1(input) << '\n';
    std::cout << "The solution to part 2 is: " << part2(input) << '\n';
}

