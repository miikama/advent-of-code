#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <optional>

struct PassportFields {
    std::optional<unsigned long int> byr; // Birth Year
    std::optional<unsigned long int> iyr; // Issue Year
    std::optional<unsigned long int> eyr; // Expiration Year
    std::optional<std::string> hgt; // Height
    std::optional<std::string> hcl; // Hair Color
    std::optional<std::string> ecl; // Eye Color
    std::optional<std::string> pid; // Passport ID
    std::optional<unsigned long int> cid; // Country ID
};

class Passport
{
public:
    Passport() = default;

    void add_field(const std::string& key, const std::string& value) {

        if(key == "byr") {
            fields.byr = std::stol(value);
            return;
        }
        if(key == "iyr") {
            fields.iyr = std::stol(value);
            return;
        }
        if(key == "eyr") {
            fields.eyr = std::stol(value);
            return;
        }
        if(key == "hgt") {
            fields.hgt = value;
            return;
        }
        if(key == "hcl") {
            fields.hcl = value;
            return;
        }
        if(key == "ecl") {
            fields.ecl = value;
            return;
        }
        if(key == "pid") {
            fields.pid = value;
            return;
        }
        if(key == "cid") {
            fields.cid = std::stol(value);
            return;
        }

    }

    bool isValid() {
        auto has_byr = fields.byr.has_value();
        auto has_iyr = fields.iyr.has_value();
        auto has_eyr = fields.eyr.has_value();
        auto has_hgt = fields.hgt.has_value();
        auto has_hcl = fields.hcl.has_value();
        auto has_ecl = fields.ecl.has_value();
        auto has_pid = fields.pid.has_value();
        auto has_cid = true; // We ignore country
        return has_byr &&
               has_iyr &&
               has_eyr &&
               has_hgt &&
               has_hcl &&
               has_ecl &&
               has_pid &&
               has_cid;
    }

private:
    PassportFields fields;
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

std::vector<Passport> read_data(const std::string &input_file)
{
    // read in data
    std::ifstream input;
    input.open(input_file);
    if (!input.is_open())
    {
        throw std::runtime_error("Could not open input file " + input_file);
    }

    std::vector<Passport> data;
    data.reserve(1000);
    std::string line;
    Passport passport {};
    while (std::getline(input, line))
    {
        if(line.size() == 0) {
            data.push_back(passport);
            passport = Passport {};
            continue;
        }
        auto contents = split_string(line, " ");
        for( auto& key_val_pair : contents) {
            auto split_pair = split_string(key_val_pair, ":");
            passport.add_field(split_pair[0], split_pair[1]);
        }
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

    auto passports = read_data(input_file);

    std::size_t valid_count{0};

    for (auto &entry : passports)
    {
        if(entry.isValid()) {
            valid_count++;
        }
    }
    std::cout << "Found " << valid_count << " / " << passports.size() << " valid entries" << std::endl;

    return 0;
}