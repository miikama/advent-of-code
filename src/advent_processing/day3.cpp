#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct PasswordField
{
    int minOccurences;
    int maxOccurences;
    char targetChar;
    std::string password;
};

std::vector<std::vector<char>> read_data(const std::string &input_file)
{
    // read in data
    std::ifstream input;
    input.open(input_file);
    if (!input.is_open())
    {
        throw std::runtime_error("Could not open input file " + input_file);
    }

    std::vector<std::vector<char>> data;
    data.reserve(1000);

    std::string line;
    std::size_t i {0};
    while (std::getline(input, line))
    {
        data.push_back(std::vector<char>(line.size()));
        for(std::size_t j = 0; j < line.size(); j++) {
            data[i][j] = line[j];
        }
        i++;
    }
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

    auto data = read_data(input_file);

    std::size_t trees = 0;
    std::size_t j = 0; 
    //Start counting trees from the second row
    for(std::size_t i = 1; i < data.size(); i++) {
        j = (3 * i) % data[i].size();
        if(data[i][j] == '#') {
            trees++;
        }
    }
    std::cout << "Counted " << trees << " trees in " << data.size() << " rows" << std::endl;
    return 0;
}