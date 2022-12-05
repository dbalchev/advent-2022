#pragma once

#include <SolutionBase.h>
#include <string>
namespace day05_ns {
    typedef char Crate;
    typedef std::vector<std::vector<Crate>> ContainerState;
    typedef std::tuple<int, int, int> Move;
    typedef std::pair<ContainerState, std::vector<Move> > ParsedData;
}

class day_05: public SolutionBase<day_05, day05_ns::ParsedData, std::string> {
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};

