#pragma once

#include <vector>


namespace day_01 {
    int solution(const char* filename);
    std::vector<std::vector<int> > read_from_file(const char* filename);
    int compute_top3_sum(std::vector<int> all_elfs_calorie_sum);
}

