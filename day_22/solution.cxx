#include <iostream>
#include <algorithm>
#include <optional>

#include <day_22.h>

day_22::ParsedData day_22::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    std::vector<std::string> map;
    std::vector<int> instructions;
    std::string line;
    while (fin) {
        std::getline(fin, line);
        if (line.empty()) {
            break;
        }
        map.push_back(std::move(line));
    }
    size_t max_width = 0;
    for (auto &row: map) {
        max_width = std::max(max_width, row.size());
    }
    for (auto &row: map) {
        row.resize(max_width, ' ');
    }
    std::getline(fin, line);
    for (int i = 0; i < line.size(); ) {
        if (line[i] == 'L') {
            instructions.push_back(-3);
            i++;
            continue;
        }
        if (line[i] == 'R') {
            instructions.push_back(-1);
            i++;
            continue;
        }
        int c = 0;
        for (; i + c < line.size() && isnumber(line[i + c]); ++c) {
            // pass
        }
        instructions.push_back(std::stoi(line.substr(i, c)));
        i += c;
    }

    return {map, instructions};
}

typedef std::tuple<int, int> TII;

static const TII DIRECTIONS[4] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
};

std::optional<TII> compute_next_position(
    const TII& current,
    int direction,
    const std::vector<std::string> &map
) {
    auto [i, j] = current;
    auto [di, dj] = DIRECTIONS[direction];
    auto ni = i + di;
    auto nj = j + dj;
    for (int num_steps = 0; num_steps < map.size() || num_steps < map[0].size(); ++num_steps) {
        if (ni == map.size()) {
            ni = 0;
        }
        if (ni == -1) {
            ni += map.size();
        }
        if (nj == map[0].size()) {
            nj = 0;
        }
        if (nj == -1) {
            nj += map[0].size();
        }
        if (ni < 0 || ni >= map.size()) {
            throw std::runtime_error("ni wrong");
        }
        if (nj < 0 || nj >= map[ni].size()) {
            throw std::runtime_error("nj wrong");
        }
        char tile_type = map[ni][nj];
        if (tile_type == '.') {
            return TII{ni, nj};
        }
        if (tile_type == '#') {
            return std::nullopt;
        }
        if (tile_type != ' ') {
            throw std::runtime_error("unknown tile type");
        }
        ni += di;
        nj += dj;
    }
    throw std::runtime_error("cannot find next pos??");
}


day_22::ResultData day_22::solve_part_1(const ParsedData& parsed_data) {
    const auto &[map, instructions] = parsed_data;
    int i = 0;
    int j = 0;
    for (; j < map[i].size(); ++j) {
        if (map[i][j] == '.') {
            break;
        }
    }
    if (j == map[i].size()) {
        throw std::runtime_error("cannot find start");
    }
    int d = 0;
    for (auto instruction: instructions) {
        if (instruction < 0) {
            d = (d - instruction) % 4;
            if (d < 0 || d > 3) {
                throw std::runtime_error("wrong d");
            }
            continue;
        }
        for (int step_no = 0; step_no < instruction; ++ step_no) {
            auto next_pos = compute_next_position(
                {i, j},
                d,
                map
            );
            if (!next_pos) {
                break;
            }
            auto [ni, nj] = next_pos.value();
            i = ni;
            j = nj;
        }
        // std::cout << i + 1 << " " << j + 1 << std::endl;
    }
    return 1'000 * (i + 1) + 4 * (j + 1) + d;
}
day_22::ResultData day_22::solve_part_2(const ParsedData& parsed_data) {
    return 30 ;
}

