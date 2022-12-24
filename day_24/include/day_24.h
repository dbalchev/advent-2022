#pragma once

#include <SolutionBase.h>
#include <tuple>
#include <vector>
#include <string>

class day_24: public SolutionBase<
    day_24, 
    std::tuple<
        std::vector<std::string>,
        std::vector<std::tuple<int, int, int, int> >
    >
>{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};

