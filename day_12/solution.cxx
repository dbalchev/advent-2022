#include <iostream>
#include <iterator>
#include <algorithm>
#include <tuple> 

#include <deque>

#include <day_12.h>


day_12::ParsedData day_12::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    std::vector<std::string> result;
    std::copy(
        std::istream_iterator<std::string>(fin),
        std::istream_iterator<std::string>(),
        std::back_insert_iterator(result)
    );
    return result;
}
static int hike(
    const day_12::ParsedData &parsed_data, 
    const std::vector<std::tuple<int, int> > &starting_points
) {
    std::deque<std::tuple<int, int, int> > visit_q;
    std::vector<std::vector<bool> > visited(
        parsed_data.size(), 
        std::vector<bool>(parsed_data[0].size(), false)
    );
    for (auto [start_r, start_c]: starting_points) {
        visit_q.push_back({start_r, start_c, 0});
        visited[start_r][start_c] = true;
    }

    auto get_height = [&](int row, int col) -> int {
        if (
            row < 0 
            || row >= parsed_data.size()
            || col < 0
            || col >= parsed_data[0].size() 
        ) {
            return 100;
        }
        char raw_h = parsed_data[row][col];
        if (raw_h == 'S') {
            raw_h = 'a';
        }
        if (raw_h == 'E') {
            raw_h = 'z';
        }
        return raw_h - 'a' + 1;
    };
    int end_distance = -1;
    while(visit_q.size() && end_distance == -1) {
        auto [r, c, d] = visit_q.front();
        visit_q.pop_front();

        int current_h = get_height(r, c);
        int next_d = d + 1;
        auto append = [&](int row, int col) {
            int next_h = get_height(row, col);
            if (current_h + 1 < next_h) {
                return;
            }
            if (parsed_data[row][col] == 'E') {
                end_distance = next_d;
                return;
            }
            if (visited[row][col]) {
                return;
            }
            visited[row][col] = true;
            visit_q.push_back({row, col, next_d});
        };
        append(r - 1, c);
        append(r + 1, c);
        append(r, c - 1);
        append(r, c + 1);
    };
    if (end_distance == -1) {
        throw std::runtime_error("cannot get to end");
    }

    return end_distance;
}
day_12::ResultData day_12::solve_part_1(const ParsedData& parsed_data) {
    int start_r = -1;
    int start_c = -1;

    for (int i = 0; i < parsed_data.size(); ++i) {
        for (int j = 0; j < parsed_data[i].size(); ++j) {
            if (parsed_data[i][j] == 'S') {
                start_r = i;
                start_c = j;
                break;
            }
        }
        if (start_r != -1) {
            break;
        }
    }
    if (start_r == -1) {
        throw std::runtime_error("Cannot find start");
    }
    return hike(parsed_data, {{start_r, start_c}});
    
}
day_12::ResultData day_12::solve_part_2(const ParsedData& parsed_data) {
    std::vector<std::tuple<int, int> > starting_points;
    for (int i = 0; i < parsed_data.size(); ++i) {
        for (int j = 0; j < parsed_data[i].size(); ++j) {
            if (parsed_data[i][j] == 'S' || parsed_data[i][j] == 'a') {
                starting_points.push_back({i, j});
            }
        }
    }
    return hike(parsed_data, starting_points);
}

