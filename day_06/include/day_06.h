#pragma once

#include <SolutionBase.h>
#include <string>

class day_06: public SolutionBase<day_06, std::string>{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};

