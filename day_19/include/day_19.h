#pragma once

#include <SolutionBase.h>
#include <tuple>
#include <vector>

namespace day_19_ns {
    typedef int d19_t;
    typedef std::vector<day_19_ns::d19_t> Resources;
    typedef std::tuple<int, std::vector<Resources> > Blueprint;
}

class day_19: public SolutionBase<
    day_19, 
    std::vector<
        day_19_ns::Blueprint
    >
>{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};

