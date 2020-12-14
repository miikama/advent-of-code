#pragma once

#include <string>

class Day
{

public:
    Day(){};
    virtual ~Day(){};

    virtual void process(const std::string &input_file) = 0;
};
