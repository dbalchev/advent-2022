#include <iostream>

#include <day_04.h>
#include <regex>
#include <algorithm>

day_04::ParsedData day_04::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    day_04::ParsedData result;
    std::regex term_regex("^(\\d+)-(\\d+),(\\d+)-(\\d+)$");
    while (fin) {
        std::string line;
        std::smatch match_results;
        fin >> line;
        if (!std::regex_match(line, match_results, term_regex)) {
            break;
        }
        std::string g1 = match_results[1].str();
        std::string g2 = match_results[2].str();
        std::string g3 = match_results[3].str();
        std::string g4 = match_results[4].str();
        result.push_back(
            std::make_pair(
                std::make_pair(
                    atoi(g1.c_str()),
                    atoi(g2.c_str())
                ),
                std::make_pair(
                    atoi(g3.c_str()),
                    atoi(g4.c_str())
                )
            )
        );
    }
    return result;
}

bool day_04::is_contained(const std::pair<int, int> &lh, const std::pair<int, int> &rh) {
    if (lh.first > rh.first) {
        return is_contained(rh, lh);
    }
    if (lh.first == rh.first) {
        return true;
    }
    // lh.first <= rh.first
    return lh.second >= rh.second;
}

bool day_04::overlaps(const std::pair<std::pair<int, int>, std::pair<int, int> > &elf_pair) {
    auto& [lh, rh] = elf_pair;
    if (lh.first > rh.first) {
        auto swapped = std::make_pair(rh, lh);
        return overlaps(swapped);
    }
    // lh.first <= rh.first
    return lh.second >= rh.first;
}

day_04::ResultData day_04::solve_part_1(const ParsedData& parsed_data) {
    int64_t fully_contained = 0;
    for (auto& [elf_1, elf_2]: parsed_data) {
        // std::cout << "processing " << elf_1.first << " " << elf_2.second << std::endl;
        fully_contained += is_contained(elf_1, elf_2);
    }

    return fully_contained;
}
day_04::ResultData day_04::solve_part_2(const ParsedData& parsed_data) {
    return std::count_if(parsed_data.begin(), parsed_data.end(), overlaps);
}

