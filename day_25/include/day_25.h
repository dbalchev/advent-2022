#pragma once

#include <vector>
#include <string>

#include <SolutionBase.h>

class day_25: public SolutionBase<day_25, std::vector<std::string>, std::string>{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
    static int64_t parse_snafu(const std::string &s);
    static std::string snafufy(int64_t n);
};

