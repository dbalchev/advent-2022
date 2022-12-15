#pragma once

#include <SolutionBase.h>
#include <tuple>
#include <vector>

namespace day_15_ns {
    typedef std::tuple<int64_t, int64_t> Location;
    typedef std::vector<std::tuple<Location, Location>> SensorData;
}

class day_15: public SolutionBase<
    day_15, 
    std::tuple<
        std::tuple<int64_t, int64_t>, 
        day_15_ns::SensorData
    >,
    int64_t
>{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};

