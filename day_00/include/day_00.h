#pragma once

#include <SolutionBase.h>

class day_00: public SolutionBase<day_00, int>{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};
