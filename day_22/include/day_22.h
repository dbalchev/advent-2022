#pragma once

#include <SolutionBase.h>
#include <tuple>
#include <string>
#include <vector>

class day_22: public SolutionBase<
    day_22,
    std::tuple<std::vector<std::string>, std::vector<int> >
>{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};

