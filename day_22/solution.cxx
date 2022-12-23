#include <iostream>
#include <algorithm>
#include <optional>
#include <cmath>
#include <functional>

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

std::optional<std::tuple<int, int, int> > compute_next_position_part_1(
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
            return std::tuple<int, int, int> {ni, nj, direction};
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

int walk(
    const std::vector<std::string> &map, 
    const std::vector<int> &instructions,
    const std::function<
        std::optional<std::tuple<int, int, int> >(const TII&, int)
    > &compute_next_position
) {
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
                {i, j}, d
            );
            if (!next_pos) {
                break;
            }
            auto [ni, nj, nd] = next_pos.value();
            i = ni;
            j = nj;
            d = nd;
            // std::cout << "(" << i + 1 << ", " << j + 1 << ")" << std::endl;
        }
        // std::cout << "====" << std::endl;
    }
    return 1'000 * (i + 1) + 4 * (j + 1) + d;
}

day_22::ResultData day_22::solve_part_1(const ParsedData& parsed_data) {
    const auto &[map, instructions] = parsed_data;
    const auto &mm = map;
    return walk(
        map, instructions, [&mm](const TII& current, int directions) {
            return compute_next_position_part_1(current, directions, mm);
        }
    );
}

/*
directions
 3
2x0
 1
*/

/*
CUBE sides
  1
2 0 3 5
  4
*/

// adjacent side and it's rotation
static const std::tuple<int, int> ADJACENCY[6][4] = {
    { // 0
        {3, 1},
        {4, 0},
        {2, 3},
        {1, 2},
    },
    { // 1
        {2, 0},
        {5, 0},
        {3, 0},
        {0, 2},
    },
    { // 2
        {4, 0},
        {5, 1},
        {1, 0},
        {0, 1},
    },
    { // 3
        {1, 0},
        {5, 3},
        {4, 0},
        {0, 3},
    },
    { // 4
        {3, 0},
        {5, 2},
        {2, 0},
        {0, 0},
    },
    { // 5
        {2, 3},
        {4, 2},
        {3, 1},
        {1, 0},
    },
};

static std::tuple<
    std::vector<std::string>,
    std::vector<std::string>
> make_block_map(
    const std::vector<std::string> &map,
    int block_size
) {
    std::vector<std::string> block_map(
        map.size() / block_size, std::string(map[0].size() / block_size, ' ')
    );
    std::vector<std::string> offset_map(
        map.size() / block_size, std::string(map[0].size() / block_size, ' ')
    );
    for (int i = 0; i < block_map.size(); ++i) {
        for (int j = 0; j < block_map[i].size(); ++j) {
            block_map[i][j] = map[i * block_size][j * block_size] == ' ' ? ' ' : '#';
        }
    }
    int i = 0;
    int j = 0;
    for (; j < block_map[i].size(); ++j) {
        if (block_map[i][j] != ' ') {
            break;
        }
    } 
    block_map[i][j] = '0';
    std::vector<std::tuple<int, int, int, int> > stack = {
        {i, j, block_map[i][j] - '0', 0}
    };

    // std::cout << std::endl;
    while (!stack.empty()) {
        auto [i, j, fn, d_offset] = stack.back();
        offset_map[i][j] = '0' + d_offset;
        // std::cout << fn << ": " << d_offset << std::endl;
        stack.pop_back();
        for (int d = 0; d < 4; ++d) {
            auto [di, dj] = DIRECTIONS[d];
            auto ai = di + i;
            auto aj = dj + j;
            if (
                ai < 0 
                || ai >= block_map.size()
                || aj < 0
                || aj >= block_map[ai].size()
                || block_map[ai][aj] != '#'
            ) {
                continue;
            }
            auto [an, ado] = ADJACENCY[fn][(d + d_offset) % 4];
            block_map[ai][aj] = '0' + an;
            stack.push_back(
                {ai, aj, an, (ado + d_offset) % 4}
            );
        }
    }
    // for (auto& line: block_map) {
    //     std::cout << line << std::endl;
    // }
    return {block_map, offset_map};
}

std::optional<std::tuple<int, int, int> > compute_next_position_part_2(
    const TII& current,
    int direction,
    const std::vector<std::string> &map,
    int block_size,
    const std::vector<std::string> &block_map,
    const std::vector<std::string> &offset_map
) {
    auto [i, j] = current;
    auto [di, dj] = DIRECTIONS[direction];
    auto ni = i + di;
    auto nj = j + dj;

    auto bi = i / block_size;
    auto bj = j / block_size;

    auto nbi = ni / block_size;
    auto nbj = nj / block_size;

    auto current_block = block_map[bi][bj] - '0';
    auto current_d_offset = offset_map[bi][bj] - '0';

    if (current_block < 0 || current_block > 5) {
        throw std::runtime_error("invalid current_block " + std::to_string(i) + " " + std::to_string(j));
    }

    if (current_block == ' ' - '0') {
        throw std::runtime_error("current block should be a number");
    }
    if (current_d_offset == ' ' - '0') {
        throw std::runtime_error("current offset should be a number");
    }

    if (
        ni >= 0
        && ni < map.size()
        && nj >= 0
        && nj < map[ni].size()
        && map[ni][nj] != ' '
    ) {
        auto next_block = block_map[nbi][nbj] - '0';
        auto next_d_offset = offset_map[nbi][nbj] - '0';
        if (next_block == ' ' - '0') {
            throw std::runtime_error("next block should be a number");
        }
        if (next_d_offset == ' ' - '0') {
            throw std::runtime_error("next offset should be a number");
        }
        if (current_block != next_block) {
            auto [expected_block, transition_offset] = ADJACENCY[current_block][
                (direction + current_d_offset) % 4
            ];
            if (next_block != expected_block) {
                throw std::runtime_error("next_block != expected_block");
            }
            if (next_d_offset != (current_d_offset + transition_offset) % 4) {
                throw std::runtime_error("next offset != expected");
            }
        }
        if (map[ni][nj] == '.') {
            return std::tuple<int, int, int> {ni, nj, direction};
        }
        return std::nullopt;
    }
    auto [next_block, transition_offset] = ADJACENCY[current_block][
        (direction + current_d_offset) % 4
    ];
    bool block_found = false;
    for (nbi = 0; nbi < block_map.size(); ++nbi) {
        for (nbj = 0; nbj < block_map[nbi].size(); ++nbj) {
            if (block_map[nbi][nbj] == '0' + next_block) {
                block_found = true;
                break;
            }
        }
        if (block_found) {
            break;
        }
    }
    if (!block_found) {
        throw std::runtime_error("didn't find next block " + std::to_string(next_block));
    }
    auto new_d_offset = offset_map[nbi][nbj] - '0';

    if (new_d_offset == ' ' - '0') {
        throw std::runtime_error("new offset should be a number");
    }

    auto li = (ni + block_size) % block_size;
    auto lj = (nj + block_size) % block_size;
    int nli, nlj;
    auto direction_delta = (-new_d_offset + transition_offset + 4 + current_d_offset) % 4;
    switch (direction_delta) {
        case 0:
            nli = li;
            nlj = lj;
            break;
        case 1:
            // 0, 0 -> 0, b - 1
            nli = lj;
            nlj = block_size - 1 - li;
            break;
        case 2:
            nli = block_size - 1 - li;
            nlj = block_size - 1 - lj;
            break;
        case 3:
            nli = block_size - 1 - lj;
            nlj = li;
            break;
    }
    ni = block_size * nbi + nli;
    nj = block_size * nbj + nlj;

    if (map[ni][nj] == ' ') {
        throw std::runtime_error("we shouldn't be nowere??");
    }
    if (map[ni][nj] == '#') {
        return std::nullopt;
    }
    if (ni >= map.size() || nj >= map[0].size()) {
        throw std::runtime_error("invalid ni, nj");
    }
    auto new_direction = (direction + direction_delta) % 4;
    
    return std::tuple<int, int, int> {ni, nj, new_direction};
    // throw std::runtime_error("not supported yet");
}

day_22::ResultData day_22::solve_part_2(const ParsedData& parsed_data) {
    const auto &[map, instructions] = parsed_data;
    
    int num_non_empty = 0;
    for (auto& line: map) {
        for (auto c: line) {
            if (c != ' ') {
                num_non_empty += 1;
            }
        }
    }
    int block_size = sqrt(num_non_empty / 6);
    auto [block_map, offset_map] = make_block_map(map, block_size);
    auto& mm = map;
    auto& bm = block_map;
    auto& om = offset_map;
    return walk(
        map, instructions, [&](const TII& current, int directions) {
            return compute_next_position_part_2(
                current, directions, mm, block_size, bm, om
            );
        }
    );}

