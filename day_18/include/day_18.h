#pragma once

#include <SolutionBase.h>
#include <vector>
#include <tuple>
namespace day_18_ns {
    typedef std::tuple<int, int, int> Cube;
}
class day_18: public SolutionBase<day_18, std::vector<day_18_ns::Cube> >{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};

