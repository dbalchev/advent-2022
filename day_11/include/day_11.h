#pragma once

#include <SolutionBase.h>
#include <vector>
#include <string>
#include <tuple>

namespace day_11_ns {
    typedef std::tuple<
        std::tuple<std::string, char, std::string>, // update op
        int, // test divisor
        std::tuple<int, int> // next monkey if passed and if not passed
    > MonkeyTransition;
    typedef std::pair<
        std::vector<int64_t>,
        MonkeyTransition
    > ParsedMonkey;
}

class day_11: public SolutionBase<day_11, std::vector<day_11_ns::ParsedMonkey>, int64_t >{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};

