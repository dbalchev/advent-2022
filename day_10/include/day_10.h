#pragma once

#include <SolutionBase.h>
#include <vector>
#include <utility> 
#include <string>

namespace day_10_ns {
    enum Instruction {
        NOOP, ADDX,
    };
}

class day_10: public SolutionBase<
    day_10, std::vector<std::pair<day_10_ns::Instruction, int> >, std::string
>{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};

