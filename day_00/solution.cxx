#include <iostream>

#include <day_00.h>

day_00::ParsedData day_00::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    int x;
    fin >> x;
    return x;
}
day_00::ResultData day_00::solve_part_1(const ParsedData& parsed_data) {
    return 20 + parsed_data;
}
day_00::ResultData day_00::solve_part_2(const ParsedData& parsed_data) {
    return 30 + parsed_data;
}
