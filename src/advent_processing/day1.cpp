#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "day1.h"

static std::vector<double> read_data(const std::string &input_file)
{
    // read in data
    std::ifstream input;
    input.open(input_file);
    if (!input.is_open())
    {
        throw std::runtime_error("Could not open input file " + input_file);
    }

    std::vector<double> numbers;
    numbers.reserve(1000);
    std::string line;
    while (std::getline(input, line))
    {
        numbers.push_back(std::stod(line));
    }
    return numbers;
}

void Day1::process(const std::string& input_file) {
    auto numbers = read_data(input_file);

    // sort
    std::sort(numbers.begin(), numbers.end());

    constexpr double target{2020};

    int end_ind = (int) numbers.size() - 1;

    while (end_ind >= 0)
    {
        for (size_t i = 0; i < numbers.size(); i++)
        {
            auto& low = numbers[i];
            auto& high = numbers[end_ind];

            if (low + high == target) {
                std::cout << "Numbers are: " << low << " x " << high << " = " << low * high << std::endl;
                return;
            }

            if( low + high > target) {
                end_ind--;
                break;
            }
        }
    }
}


int main(int argc, char **argv)
{
    // take input file as argument
    if (argc != 2)
    {
        // throw std::runtime_error("Give the input file as argument");
    }
    std::string input_file{argv[1]};

    Day1 day;
    day.process(input_file);

    return 0;
}

