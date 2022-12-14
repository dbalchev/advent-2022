#include <iostream>
#include <string>

#include <range/v3/view.hpp>

#include <day_14.h>

static const char START = 's';
static const char END = 'e';

day_14::ParsedData day_14::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    ParsedData result;
    while (fin) {
        std::string line;
        std::getline(fin, line);
        if (line.empty()) {
            break;
        }
        result.push_back(
            line
            | ranges::views::split(std::string(" -> "))
            | ranges::views::transform([](auto point_str_range) -> std::tuple<int, int> {
                auto coordinates_range = 
                    point_str_range
                    | ranges::views::split(std::string(","))
                    | ranges::views::transform([](auto coord_str_range){
                        return std::stoi(ranges::to<std::string>(coord_str_range));
                    });
                auto begin = coordinates_range.begin();
                auto end = coordinates_range.end();
                if (begin == end) {
                    throw std::range_error("cannot get x");
                }
                int x = *begin;
                begin++;
                if (begin == end) {
                    throw std::range_error("cannot get y");
                }
                int y = *begin;
                begin++;
                if (begin != end) {
                    throw std::range_error("more than x,y");
                }
                return {x, y};
            })
        | ranges::to<std::vector>()
        );
    }
    return result;
}
int day_14::simulate(const ParsedData& parsed_data, bool add_floor) {
    int max_x = 0;
    int max_y = 0;
    for (auto &[x, y]: ranges::views::join(parsed_data)){
        max_x = std::max(x, max_x);
        max_y = std::max(y, max_y);
    }
    if (add_floor) {
        max_x = std::max(max_x, 500 + max_y + 10);
    }
    std::vector<std::vector<char> > cross_section(
        max_x + 1, std::vector<char>(max_y + 1, '.')
    );
    for (auto& line: parsed_data) {
        for (int i = 0; i < line.size() - 1; ++i) {
            auto [start_x, start_y] = line[i];
            auto [end_x, end_y] = line[i + 1];

            if (start_x == end_x) { 
                int y1 = std::min(start_y, end_y);
                int y2 = std::max(start_y, end_y);
                for (int y = y1; y <= y2; ++y) {
                    cross_section[start_x][y] = '#';
                }
            } else if (start_y == end_y) {
                int x1 = std::min(start_x, end_x);
                int x2 = std::max(start_x, end_x);
                for (int x = x1; x <= x2; ++x) {
                    cross_section[x][start_y] = '#';
                }
            }
        }
    }
    if (add_floor) {
        for (auto &col: cross_section) {
            col.push_back('.');
            col.push_back('#');
        }
    }
    int n_sand_units = 0;
    std::vector<std::tuple<int, int, char> >bt_stack = {{500, 0, START}};
    while(!bt_stack.empty()) {
        auto [x, y, state] = bt_stack.back();
        bt_stack.pop_back();
        if (x >= cross_section.size() || x < 0 || y >= cross_section[0].size()) {
            if (add_floor) {
                std::cerr << cross_section.size() << " " << cross_section[0].size() << std::endl;
                std::cerr << x << " " << y << std::endl;
                throw std::runtime_error("floor not infinite enough ");
            }
            break;
        }
        if (cross_section[x][y] != '.') {
            continue;
        }
        if (state == START) {
            bt_stack.push_back({x, y, END});
            bt_stack.push_back({x + 1, y + 1, START});
            bt_stack.push_back({x - 1, y + 1, START});
            bt_stack.push_back({x, y + 1, START});
        } else if (state == END) {
            n_sand_units += 1;
            cross_section[x][y] = 'O';
        } else {
            throw std::runtime_error("unknown state");
        }
    }
    if (!add_floor && bt_stack.empty()) {
        throw std::runtime_error("cloggged");
    }
    return n_sand_units;
}

day_14::ResultData day_14::solve_part_1(const ParsedData& parsed_data) {
    return simulate(parsed_data, false);
}
day_14::ResultData day_14::solve_part_2(const ParsedData& parsed_data) {
    return simulate(parsed_data, true);
}

