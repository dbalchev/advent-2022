#pragma once

#include <SolutionBase.h>
#include <tuple>
#include <vector>

namespace day_16_ns {
    typedef std::tuple<int, std::vector<int> > Node;

}

class day_16: public SolutionBase<day_16, std::vector<day_16_ns::Node> >{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};

