#pragma once

#include <SolutionBase.h>
#include <vector> 
#include <string>

class day_03: public SolutionBase<day_03, std::vector<std::string> > {
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};

