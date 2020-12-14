#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <optional>
#include <cmath>
#include <set>

#include "day6.h"

struct Group
{
    std::vector<std::string> answers;
};

// one of the splitting ways https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> split_string(const std::string &input, const std::string &delimeter)
{

    std::vector<std::string> splitted{};
    size_t start = 0;
    auto end = input.find(delimeter);
    while (end != std::string::npos)
    {
        splitted.push_back(input.substr(start, end - start));
        start = end + delimeter.length();
        end = input.find(delimeter, start);
    }
    splitted.push_back(input.substr(start, end - start));

    return splitted;
}

std::vector<Group> read_data(const std::string &input_file)
{
    // read in data
    std::ifstream input;
    input.open(input_file);
    if (!input.is_open())
    {
        throw std::runtime_error("Could not open input file " + input_file);
    }

    std::vector<Group> data;
    data.reserve(1000);
    std::string line;
    Group group{};

    while (std::getline(input, line))
    {
        if (line.size() == 0)
        {
            data.push_back(group);
            group = Group {};
            continue;
        }

        group.answers.push_back(line);

    }
    data.push_back(group);
    return data;
}

int main(int argc, char **argv)
{

    // take input file as argument
    if (argc != 2)
    {
        throw std::runtime_error("Give the input file as argument");
    }
    std::string input_file{argv[1]};

    auto groups = read_data(input_file);

    size_t sum {0};
    for(auto& group: groups) {

        std::set<char> unique_yesses;
        for(auto& person: group.answers) {
            for(auto& question : person) {
                unique_yesses.insert(question);
            }
        }
        sum += unique_yesses.size();
    }

    std::cout << "Sum of unique 'yes' answers: " << sum << " for " << groups.size() << " groups " << std::endl;

    return 0;
}