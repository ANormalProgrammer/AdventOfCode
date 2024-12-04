#include <iostream>
#include <vector>
#include <string>

enum class Directions
{
    any,
    top_left,
    top_middle,
    top_right,
    middle_left,
    middle_right,
    bottom_left,
    bottom_middle,
    bottom_right
};

struct Position
{
    int x;
    int y;
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


long long word_search(const std::vector<std::string>& puzzle, const std::string& word,
                      Position position,  int character, Directions direction)
{
    if(position.x < 0 || position.x >= puzzle.size()) return 0;
    if(position.y < 0 || position.y >= puzzle[0].size()) return 0;

    if(puzzle[position.x][position.y] != word[character]) return 0;
    else if(character + 1 == word.size()) return 1;
    else
    {
        if(direction == Directions::top_left)
        {
            return word_search(puzzle, word,{position.x - 1, position.y - 1}, character + 1, direction);
        }
        else if(direction == Directions::top_middle)
        {
            return word_search(puzzle, word,{position.x - 1, position.y}, character + 1, direction);
        }
        else if(direction == Directions::top_right)
        {
            return word_search(puzzle, word,{position.x - 1, position.y + 1}, character + 1, direction);
        }
        else if(direction == Directions::middle_left)
        {
            return word_search(puzzle, word,{position.x, position.y - 1}, character + 1, direction);
        }
        else if(direction == Directions::middle_right)
        {
            return word_search(puzzle, word,{position.x, position.y + 1}, character + 1, direction);
        }
        else if(direction == Directions::bottom_left)
        {
            return word_search(puzzle, word,{position.x + 1, position.y - 1}, character + 1, direction);
        }
        else if(direction == Directions::bottom_middle)
        {
            return word_search(puzzle, word,{position.x + 1, position.y}, character + 1, direction);
        }
        else if(direction == Directions::bottom_right)
        {
            return word_search(puzzle, word,{position.x + 1, position.y + 1}, character + 1, direction);
        }
        else
        {
            return word_search(puzzle, word,{position.x - 1, position.y - 1}, character + 1, Directions::top_left)
                +  word_search(puzzle, word,{position.x - 1, position.y}, character + 1, Directions::top_middle)
                +  word_search(puzzle, word,{position.x - 1, position.y + 1}, character + 1, Directions::top_right)
                +  word_search(puzzle, word,{position.x, position.y - 1}, character + 1, Directions::middle_left)
                +  word_search(puzzle, word,{position.x, position.y + 1}, character + 1, Directions::middle_right)
                +  word_search(puzzle, word,{position.x + 1, position.y - 1}, character + 1, Directions::bottom_left)
                +  word_search(puzzle, word,{position.x + 1, position.y}, character + 1, Directions::bottom_middle)
                +  word_search(puzzle, word,{position.x + 1, position.y + 1}, character + 1, Directions::bottom_right);
        }
    }
}

long long part1(const std::vector<std::string> &input)
{
    long long number_of_words = 0;
    for(int x = 0; x < input.size(); ++x)
    {
        for(int y = 0; y < input[0].size(); ++y)
        {
            number_of_words += word_search(input, "XMAS", {x, y}, 0, Directions::any);
        }
    }
    return number_of_words;
}
long long part2(const std::vector<std::string> &input)
{
    long long number_of_words = 0;
    for(int x = 0; x < input.size(); ++x)
    {
        for(int y = 0; y < input[0].size(); ++y)
        {
            if(word_search(input, "MAS", {x, y}, 0, Directions::bottom_right) == 1
            || word_search(input, "MAS", {x + 2, y + 2}, 0, Directions::top_left) == 1)
            {
                if(word_search(input, "MAS", {x, y + 2}, 0, Directions::bottom_left) == 1
                || word_search(input, "MAS", {x + 2, y}, 0, Directions::top_right) == 1)

                    ++number_of_words;
            }
        }
    }
    return number_of_words;
}

int main(int argc, char** argv)
{
    if(argc == 1)
        std::freopen("day4inp.txt", "r", stdin);
    else
        std::freopen(argv[1], "r", stdin);

    std::vector<std::string>  input = processInput();
    
    std::cout << "The solution to part 1 is: " << part1(input) << '\n';
    std::cout << "The solution to part 2 is: " << part2(input) << '\n';
}






