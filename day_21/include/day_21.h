#pragma once

#include <SolutionBase.h>
#include <tuple>
#include <variant>
#include <vector>
#include <unordered_map>

namespace day_21_ns {
    typedef std::tuple<
        std::string,
        char,
        std::string
    > OpMonkey;
    typedef std::variant<int64_t, OpMonkey> Monkey;
};

class day_21: public SolutionBase<
    day_21, 
    std::unordered_map<std::string, day_21_ns::Monkey>,
    int64_t
>{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};

