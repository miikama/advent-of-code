#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <optional>
#include <cmath>

struct Position
{
    int column;
    int row;
};

enum class Partition
{
    Front,
    Back,
    Left,
    Right,
};

struct BoardingPass
{
    std::vector<Partition> rows;
    std::vector<Partition> columns;
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

std::vector<BoardingPass> read_data(const std::string &input_file)
{
    // read in data
    std::ifstream input;
    input.open(input_file);
    if (!input.is_open())
    {
        throw std::runtime_error("Could not open input file " + input_file);
    }

    std::vector<BoardingPass> data;
    data.reserve(1000);
    std::string line;
    BoardingPass passport{};
    while (std::getline(input, line))
    {
        if (line.size() == 0)
        {
            continue;
        }

        std::vector<Partition> rows;
        rows.reserve(7);
        std::vector<Partition> columns;
        columns.reserve(3);
        for (size_t i = 0; i < line.size(); i++)
        {

            if (line[i] == 'B')
            {
                rows.push_back(Partition::Back);
            }
            else if (line[i] == 'F')
            {
                rows.push_back(Partition::Front);
            }
            else if (line[i] == 'R')
            {
                columns.push_back(Partition::Right);
            }
            else if (line[i] == 'L')
            {
                columns.push_back(Partition::Left);
            }
            else
            {
                throw std::runtime_error("Incorrect input");
            }
        }
        if(rows.size() != 7 || columns.size() != 3) {
            throw std::runtime_error("Failed parsing input.");
        }
        data.push_back(BoardingPass{rows, columns});
    }
    return data;
}

int binary_search(int initial_min, int initial_max, const std::vector<Partition> &partitions)
{

    int row_min = initial_min;
    int row_max = initial_max;
    for (size_t i = 0; i < partitions.size(); i++)
    {
        // Do the Front/Back and Left/Right partitions in the same place
        switch (partitions[i])
        {
        case Partition::Front:
            row_max = std::floor(row_max - (row_max - row_min) / 2.0);
            break;
        case Partition::Back:
            row_min = std::ceil(row_min + (row_max - row_min) / 2.0);
            break;
        case Partition::Left:
            row_max = std::floor(row_max - (row_max - row_min) / 2.0);
            break;
        case Partition::Right:
            row_min = std::ceil(row_min + (row_max - row_min) / 2.0);
            break;
        default:
            break;
        }
    }

    if (row_min != row_max)
    {
        throw std::runtime_error("Failed");
    }
    return row_min;
}

std::vector<Position> parse_positions(const std::vector<BoardingPass> &passes)
{
    std::vector<Position> positions(passes.size());

    for (size_t i = 0; i < passes.size(); ++i)
    {
        positions[i].row = binary_search(0, 127, passes[i].rows);
        positions[i].column = binary_search(0, 7, passes[i].columns);
    }
    return positions;
}

int main(int argc, char **argv)
{

    // take input file as argument
    if (argc != 2)
    {
        throw std::runtime_error("Give the input file as argument");
    }
    std::string input_file{argv[1]};

    auto passes = read_data(input_file);

    std::vector<Position> positions = parse_positions(passes);
    std::vector<unsigned int> seat_ids(positions.size(), 0);

    for(size_t i = 0; i < seat_ids.size(); ++i) {
        seat_ids[i] = positions[i].row * 8 + positions[i].column;
    }

    auto largest_element_ind = std::distance(seat_ids.begin(), std::max_element(seat_ids.begin(), seat_ids.end()));

    std::cout << "Found largest SeatID: " << seat_ids[largest_element_ind] << " at index: " << largest_element_ind << " / " << passes.size() << " passes" << std::endl;

    return 0;
}