#pragma once

#include <SolutionBase.h>

namespace day_09_ns {
    typedef std::pair<int, int> Position;
    typedef std::pair<char, int> Instruction;
}

class day_09: public SolutionBase<
    day_09, std::vector<day_09_ns::Instruction> 
>{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};

