#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <day_01.h>

std::vector<std::vector<int> > day_01::read_from_file(const char* filename) {
    std::filesystem::path filepath = std::filesystem::absolute(filename);
    std::ifstream fin(filepath);
    std::vector<std::vector<int> > result;
    if (!fin) {
        throw std::runtime_error("Cannot read from file " + filepath.string());
    }
    while(fin) {
        result.push_back(std::vector<int>());
        auto &current_vector = result.back();

        while(true) {
            std::string next_line;
            std::getline(fin, next_line);
            if (!next_line.length()) {
                break;
            }
            std::stringstream line_stream(next_line);
            int x;
            line_stream >> x;
            current_vector.push_back(x);
        }
    }
    return result;
}

int day_01::compute_top3_sum(std::vector<int> all_elfs_calorie_sum) {
    auto mid = all_elfs_calorie_sum.end() - 3;
    std::nth_element(all_elfs_calorie_sum.begin(), mid, all_elfs_calorie_sum.end());
    return std::reduce(mid, all_elfs_calorie_sum.end());
}


using namespace day_01;

int day_01_solution(const char* input_filename) {
    auto all_elf_calories = read_from_file(input_filename);
    std::vector<int> sums;
    for (auto& elf_calories: all_elf_calories) {
        sums.push_back(std::reduce(elf_calories.begin(), elf_calories.end()));
    }

    std::cout << "Part 1: " << *std::max_element(sums.begin(), sums.end()) << std::endl;
    std::cout << "Part 2: " << compute_top3_sum(sums) << std::endl;
    return 0;
}

