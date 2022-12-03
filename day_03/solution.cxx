#include <iostream>
#include <utility>
#include <day_03.h>
#include <set>
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
        auto half_len = x.length() / 2;
        results.push_back(std::make_pair(
            x.substr(0, half_len), x.substr(half_len, x.length())
        ));
    }
    
    return results;
}
day_03::ResultData day_03::solve_part_1(const ParsedData& parsed_data) {
    int64_t result = 0;
    for (auto& sack: parsed_data) {
        std::set<char> comp_1(sack.first.begin(), sack.first.end());
        std::set<char> comp_2(sack.second.begin(), sack.second.end());
        std::vector<char> intersection;
        std::copy_if(
            comp_1.begin(), comp_1.end(), 
            std::back_insert_iterator(intersection),
            [&](char c) -> bool {return comp_2.count(c);}
        );
        if (intersection.size() != 1) {
            std::stringstream ss;
            ss << "Intersection has length " << intersection.size();
            throw std::runtime_error(ss.str());
        }
        char intersection_c = intersection.back();
        if (std::isupper(intersection_c)) {
            result += intersection_c - 'A' + 27;
        } else {
            result += intersection_c - 'a' + 1;
        }
    }
    return result;
}
day_03::ResultData day_03::solve_part_2(const ParsedData& parsed_data) {
    return 31;
}

