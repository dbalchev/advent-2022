#pragma once

#include <SolutionBase.h>

#include <tuple>
#include <vector>

class day_23: public SolutionBase<
    day_23, 
    std::vector<std::tuple<int, int> >
>{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};

