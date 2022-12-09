#pragma once

#include <SolutionBase.h>
#include <utility>
#include <memory>
#include <unordered_map>
#include <vector>

namespace day_07_ns {
    
    struct DirEntry{
        std::unordered_map<std::string, int64_t> files;
        std::unordered_map<std::string, DirEntry> directories;

        inline bool operator==(const day_07_ns::DirEntry& rh) const {
                return files == rh.files && directories == rh.directories;
            }
        };
}


class day_07: public SolutionBase<day_07, day_07_ns::DirEntry, int64_t>{
public:
    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);
};

