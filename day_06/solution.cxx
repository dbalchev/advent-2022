#include <iostream>

#include <unordered_set>
#include <algorithm>
#include <day_06.h>


day_06::ParsedData day_06::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    std::string x;
    fin >> x;
    return x;
}

static int lookup_unique_sequence(const std::string& data, int n_unique) {
    for (int i = 0; i + n_unique < data.length(); ++i) {
        std::unordered_set<char> window(
            data.begin() + i, data.begin() + i + n_unique
        );
        if (window.size() == n_unique) {
            return i + n_unique;
        }
    }
    return -1;
}

day_06::ResultData day_06::solve_part_1(const ParsedData& parsed_data) {
    return lookup_unique_sequence(parsed_data, 4);
}
day_06::ResultData day_06::solve_part_2(const ParsedData& parsed_data) {
    return lookup_unique_sequence(parsed_data, 14);
}

