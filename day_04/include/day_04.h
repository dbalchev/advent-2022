#pragma once

#include <SolutionBase.h>
#include <vector>
#include <utility>

class day_04: public SolutionBase<
    day_04, 
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > >
>{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
    
    static bool is_contained(const std::pair<int, int> &lh, const std::pair<int, int> &rh);
    static bool day_04::overlaps(const std::pair<std::pair<int, int>, std::pair<int, int> > &elf_pair);
};

