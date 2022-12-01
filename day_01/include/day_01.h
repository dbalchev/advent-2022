#pragma once

#include <vector>



int day_01_solution(const char* filename);

namespace day_01 {
    std::vector<std::vector<int> > read_from_file(const char* filename);
    int compute_top3_sum(std::vector<int> all_elfs_calorie_sum);
}

