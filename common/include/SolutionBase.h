#pragma once

#include <cstdint>
#include <fstream>
#include <filesystem>

template <typename Implementation, typename ParsedDataT, typename ResultDataT = int64_t>
class SolutionBase {
public:
    typedef ParsedDataT ParsedData;
    typedef ResultDataT ResultData;

    static inline std::ifstream open_for_reading(const char* filename) {
        std::filesystem::path filepath = std::filesystem::absolute(filename);
        std::ifstream fin(filepath);
        if (!fin) {
            throw std::runtime_error("Cannot read from file " + filepath.string());
        }
        return fin;
    }

    // static ParsedData parse_input(const char* filename);
    // static ResultData solve_part_1(const ParsedData& parsed_data);
    // static ResultData solve_part_2(const ParsedData& parsed_data);

    static int solution(const char* input_filename) {
        auto parsed_data = Implementation::parse_input(input_filename);
        std::cout << "Part 1: " << Implementation::solve_part_1(parsed_data) << std::endl;
        std::cout << "Part 2: " << Implementation::solve_part_2(parsed_data) << std::endl;

        return 0;
    }

};
