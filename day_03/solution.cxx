#include <iostream>
#include <utility>
#include <day_03.h>
#include <algorithm>
#include <iterator>
#include <sstream>


day_03::ParsedData day_03::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    day_03::ParsedData results;
    while (fin) {
        std::string x;
        fin >> x;
        if (!x.length()) {
            continue;
        }
        results.push_back(x);
    }
    
    return results;
}

static int iterm_priority(char item) {
    if (std::isupper(item)) {
        return item - 'A' + 27;
    } else {
        return item - 'a' + 1;
    }
}

static std::vector<char> unique_sorted(const std::string &items) {
    std::vector<char> v(items.begin(), items.end());
    std::sort(v.begin(), v.end());
    auto end = std::unique(v.begin(), v.end());
    v.resize(end - v.begin());
    return v;
}

day_03::ResultData day_03::solve_part_1(const ParsedData& parsed_data) {
    int64_t result = 0;
    for (auto& sack: parsed_data) {
        auto half_len = sack.length() / 2;

        std::vector<char> comp_1 = unique_sorted(sack.substr(0, half_len));
        std::vector<char> comp_2 = unique_sorted(sack.substr(half_len, sack.length()));

        std::vector<char> compartment_intersection;
        std::set_intersection(
            comp_1.begin(), comp_1.end(), 
            comp_2.begin(), comp_2.end(),
            std::back_insert_iterator(compartment_intersection)
        );
        if (compartment_intersection.size() != 1) {
            std::stringstream ss;
            ss << "Intersection has length " << compartment_intersection.size() << std::endl;
            ss << std::string(comp_1.begin(), comp_1.end()) << " " << std::string(comp_2.begin(), comp_2.end()) << std::endl;
            ss << std::string(compartment_intersection.begin(), compartment_intersection.end()) << std::endl;
            throw std::runtime_error(ss.str());
        }
        result += iterm_priority(compartment_intersection.back());
    }
    return result;
}
day_03::ResultData day_03::solve_part_2(const ParsedData& parsed_data) {
    int64_t result = 0;
    for (int i = 0; i < parsed_data.size(); i += 3) {
        auto elf_1 = unique_sorted(parsed_data[i]);
        auto elf_2 = unique_sorted(parsed_data[i + 1]);
        auto elf_3 = unique_sorted(parsed_data[i + 2]);

        std::vector<char> intersection_12, intersection_123;
        std::set_intersection(
            elf_1.begin(), elf_1.end(), 
            elf_2.begin(), elf_2.end(),
            std::back_insert_iterator(intersection_12)
        );

        std::set_intersection(
            intersection_12.begin(), intersection_12.end(), 
            elf_3.begin(), elf_3.end(),
            std::back_insert_iterator(intersection_123)
        );
        if (intersection_123.size() != 1) {
            std::stringstream ss;
            ss << "Intersection has length " << intersection_123.size() << std::endl;
            throw std::runtime_error(ss.str());
        }
        result += iterm_priority(intersection_123.back());
    }
    return result;
}
