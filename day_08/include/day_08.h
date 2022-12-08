#pragma once

#include <SolutionBase.h>

class day_08: public SolutionBase<day_08, std::vector<std::string> >{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
    static std::vector<std::vector<bool> > compute_left_visibility_mask(
        const day_08::ParsedData& tree_heights
    );
    static std::vector<std::vector<bool> > compute_top_visibility_mask(
        const day_08::ParsedData& tree_heights
    );
    static std::vector<std::vector<int> > compute_left_visibility_distances(
        const day_08::ParsedData& tree_heights
    );
    static std::vector<std::vector<int> > compute_top_visibility_distances(
        const day_08::ParsedData& tree_heights
    );
};

