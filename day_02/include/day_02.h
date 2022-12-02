#pragma once
#include <vector>
#include <utility>

namespace day_02{
    int solution(const char* filename);
    std::vector<std::pair<int, int> > parse_input(const char* filename);
    int score_part_1(const std::vector<std::pair<int, int> > &plan);
    int score_part_2(const std::vector<std::pair<int, int> > &plan);
}


