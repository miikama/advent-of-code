#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "day2.h"

struct PasswordField
{
    unsigned int minOccurences;
    unsigned int maxOccurences;
    char targetChar;
    std::string password;
};

// one of the splitting ways https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
static std::vector<std::string> split_string(const std::string &input, const std::string &delimeter)
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

static std::vector<PasswordField> read_data(const std::string &input_file)
{
    // read in data
    std::ifstream input;
    input.open(input_file);
    if (!input.is_open())
    {
        throw std::runtime_error("Could not open input file " + input_file);
    }

    std::vector<PasswordField> data;
    data.reserve(1000);
    std::string line;
    while (std::getline(input, line))
    {
        auto contents = split_string(line, " ");
        auto count_split = split_string(contents[0], "-");
        data.push_back(
            PasswordField{                
                (unsigned) std::stoi(count_split[0]),
                (unsigned) std::stoi(count_split[1]),
                contents[1][0],
                contents[2],
            });
    }
    return data;
}

void Day2::process(const::std::string& input_file) {

    auto data = read_data(input_file);

    std::size_t valid_count{0};

    for (auto &entry : data)
    {
        std::size_t letter_cout = std::count(entry.password.begin(), entry.password.end(), entry.targetChar);
        if (letter_cout >= entry.minOccurences && letter_cout <= entry.maxOccurences)
        {
            valid_count++;
        }
    }
    std::cout << "Found " << valid_count << " / " << data.size() << " valid entries" << std::endl;
}

// int main(int argc, char **argv)
// {

//     // take input file as argument
//     if (argc != 2)
//     {
//         throw std::runtime_error("Give the input file as argument");
//     }
//     std::string input_file{argv[1]};

//     Day2 day;
//     day.process(input_file);

//     return 0;

// }