#include <iostream>
#include <tuple>
#include <vector>
#include <numeric>

#include <range/v3/view.hpp>

#include <day_17.h>

day_17::ParsedData day_17::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    std::string x;
    fin >> x;
    return x;
}

typedef std::tuple<int, int> Position;
typedef std::vector<std::vector<char> > State;

const static std::vector<std::vector<Position> > PIECES = {
    {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
    {{0, 1}, {1, 0}, {1, 1}, {1, 2}, {2, 1}},
    {{0, 0}, {0, 1}, {0, 2}, {1, 2}, {2, 2}},
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
    {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
};

static std::vector<Position> move_piece(const std::vector<Position> &piece, int dy, int dx) {
    return piece
        | ranges::views::transform([=](auto &yx) -> Position {
            auto [y, x] = yx;
            return {dy + y, dx + x};
        })
        | ranges::to<std::vector>();
}

static bool has_colisions(const std::vector<Position> &piece, const State &state) {
    for (auto& [y, x]: piece) {
        if (y < 0 || x < 0 || x >= 7 || state[y][x] != '.') {
            return true;
        }
    }
    return false;
}

static std::vector<int> simulate(const day_17::ParsedData &parsed_data, int n_rocks) {
    State state;
    int highest_y = -1;
    int next_piece_index = 0;
    int next_jet_index = 0;
    std::vector<int> per_step_heights;

    for (int rock_index = 0; rock_index < n_rocks; ++rock_index) {
        auto piece = move_piece(PIECES[next_piece_index++], highest_y + 4, 2);
        next_piece_index %= PIECES.size();

        state.resize(highest_y + 10, std::vector<char>(7, '.'));
        if (has_colisions(piece, state)) {
            throw std::runtime_error("Initial collision?");
        }
        while (true) {
            int dx = parsed_data[next_jet_index++] == '<' ? -1 : 1;
            next_jet_index %= parsed_data.size();

            {
                auto jet_piece = move_piece(piece, 0, dx);
                if (!has_colisions(jet_piece, state)) {
                    piece = std::move(jet_piece);
                }
            }

            auto falling_piece = move_piece(piece, -1, 0);
            if (has_colisions(falling_piece, state)) {
                for (auto [y, x]: piece) {
                    if (state[y][x] != '.') {
                        throw std::runtime_error("overriding rock?");
                    }
                    state[y][x] = '#';
                    highest_y = std::max(highest_y, y);
                }
                break;
            }
            piece = std::move(falling_piece);
        }
        per_step_heights.push_back(highest_y + 1);
        // for (auto &line: state | ranges::views::reverse) {
        //     std::cout << std::string(line.begin(), line.end()) << std::endl;
        // }
        // std::cout << std::endl;
    }

    return per_step_heights;
} 

day_17::ResultData day_17::solve_part_1(const ParsedData& parsed_data) {
    return simulate(parsed_data, 2022).back();
}
day_17::ResultData day_17::solve_part_2(const ParsedData& parsed_data) {
    // state = 2 ** (interesting_height * 7) x parsed_data.size()
    int n_cycles = 3'000;
    int warmup = 500;
    int max_cycle_size = 2'000;
    int cycle_size = -1;
    auto heights = simulate(parsed_data, n_cycles * parsed_data.size());
    std::vector<int> deltas;
    for (int i = 0; i + 1 < n_cycles; ++i){
        deltas.push_back(heights[parsed_data.size() * (i + 1)] - heights[parsed_data.size() * i]);
        // std::cout << deltas.back() << std::endl;
    }
    for (int c = 1; c < max_cycle_size - 1; ++c) {
        std::vector<int> a(deltas.begin() + warmup, deltas.end() - c);
        std::vector<int> b(deltas.begin() + warmup + c, deltas.end());
        if (a.size() != b.size()) {
            throw std::runtime_error("a != b");
        }
        if (a == b) {
            cycle_size = c;
            break;
        }
    }
    if (cycle_size == -1) {
        throw std::runtime_error("Cannot find a delta cycle");
    }
    
    int64_t required_n_steps = 1'000'000'000'000;
    int warmup_rocks = warmup * parsed_data.size();
    int cycle_rocks = cycle_size * parsed_data.size();

    int64_t n_required_cycles = (required_n_steps - warmup_rocks) / cycle_rocks;
    int64_t offset_rocks = required_n_steps - warmup_rocks - n_required_cycles * cycle_rocks;
    std::cout << "offset_rocks " << offset_rocks << std::endl;
    int64_t cycle_height_delta = std::accumulate(
        deltas.begin() + warmup, deltas.begin() + warmup + cycle_size, 0
    );

    return heights[warmup_rocks] + n_required_cycles * cycle_height_delta + (
        heights[warmup_rocks + offset_rocks] - heights[warmup_rocks] - 1
    );
}

