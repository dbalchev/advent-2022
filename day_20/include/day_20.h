#pragma once

#include <SolutionBase.h>
#include <vector>
#include <algorithm>

class day_20: public SolutionBase<day_20, std::vector<int64_t>, int64_t >{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);

    template<typename iterator_type>
    static void move(
        iterator_type begin,
        iterator_type end,
        iterator_type current_pos,
        int64_t n_moves
    ) {
        auto next = current_pos + 1;
        for (int64_t i = 0; i < n_moves; ++i) {
            if (next == end) {
                std::rotate(begin, current_pos, end);
                next = begin;
                i--;
            } else {
                std::swap(*current_pos, *next);
            }
            current_pos = next;
            next = next + 1;
        }
    }
};

