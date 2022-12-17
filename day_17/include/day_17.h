#pragma once

#include <SolutionBase.h>
#include <string>

class day_17: public SolutionBase<
    day_17, std::string, int64_t
>{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};

