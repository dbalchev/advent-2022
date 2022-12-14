#pragma once

#include <SolutionBase.h>
#include <tuple>
#include <vector>

class day_14: public SolutionBase<
    day_14, 
    std::vector<std::vector<std::tuple<int, int> > > 
>{
private:
    static int simulate(const ParsedData& parsed_data, bool add_floor);
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};

