#include <iostream>
#include <unordered_set>

#include <range/v3/view.hpp>
// #include <range/v3/v>


#include <day_23.h>
#include <TupleHash.h>

typedef std::tuple<int, int> tii;
typedef std::vector<tii> vtii;

day_23::ParsedData day_23::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    ParsedData result;
    int row_no = 0;
    std::string line;
    while(std::getline(fin, line) && !line.empty()) {
        for (auto [col_no, c]: ranges::views::enumerate(line)) {
            if (c == '#') {
                result.push_back({row_no, col_no});
            }
        }
        row_no++;
    }
    return result;
}

static const tii DIRECTIONS[4][3] = {
    {{-1, 0}, {-1, 1}, {-1, -1}},
    {{1, 0}, {1, 1}, {1, -1}},
    {{0, -1}, {-1, -1}, {1, -1}},
    {{0, 1}, {-1, 1}, {1, 1}},
};

static vtii move_elfs(
    const vtii& positions,
    int direction_offset 
) {
    std::unordered_set<tii> pos_set;
    vtii destinations;

    pos_set.insert(positions.begin(), positions.end());

    for (const auto& [i, j]: positions) {
        int proposed_direction = -1;
        bool needs_to_move = false;
        for (int di = -1; di < 2; ++ di) {
            for (int dj = -1; dj < 2; ++dj) {
                if (di == 0 && dj == 0) {
                    continue;
                }
                needs_to_move = needs_to_move || pos_set.contains({i + di, j + dj});
            }
        }
        for (int direciton_index = 0; needs_to_move && direciton_index < 4; ++direciton_index) {
            int d = (direciton_index + direction_offset) % 4;
            bool valid_d = true;
            for (int v = 0; v < 3; ++v) {
                auto [di, dj] = DIRECTIONS[d][v];
                valid_d = valid_d && !pos_set.contains({i + di, j + dj});
            }
            if (valid_d) {
                proposed_direction = d;
                break;
            }
        }
        tii next_pos = {i, j};
        if (proposed_direction != -1) {
            auto [di, dj] = DIRECTIONS[proposed_direction][0];
            next_pos = {i + di, j + dj};
        }
        destinations.push_back(next_pos);
    }

    std::unordered_multiset<tii> dest_set(destinations.begin(), destinations.end());

    for (int i = 0; i< destinations.size(); ++i) {
        if (dest_set.count(destinations[i]) > 1) {
            destinations[i] = positions[i];
        }
    }
    return destinations;
}

day_23::ResultData day_23::solve_part_1(const ParsedData& parsed_data) {
    auto positions = parsed_data;
    for (int i = 0; i < 10; ++i) {
        positions = move_elfs(std::move(positions), i % 4);
    }
    auto i_range = positions | ranges::views::transform([](auto ij) {
        return std::get<0>(ij);
    });
    auto j_range = positions | ranges::views::transform([](auto ij) {
        return std::get<1>(ij);
    });
    auto [min_i_it, max_i_it] = std::minmax_element(i_range.begin(), i_range.end());
    auto [min_j_it, max_j_it] = std::minmax_element(j_range.begin(), j_range.end());
    int min_i = *min_i_it;
    int max_i = *max_i_it;
    int min_j = *min_j_it;
    int max_j = *max_j_it;
    
    // std::vector<std::string> viz(max_i - min_i + 1, std::string(max_j - min_j + 1, '.'));
    // for (auto [i, j]: positions) {
    //     viz[i - min_i][j - min_j] = '#';
    // }

    // for (auto &line: viz) {
    //     std::cout << line << std::endl;
    // }


    return (max_i - min_i + 1) * (max_j - min_j + 1) - positions.size();
}
day_23::ResultData day_23::solve_part_2(const ParsedData& parsed_data) {
    auto positions = parsed_data;
    for (int i = 0; i < 1'000; ++i) {
        auto new_positions = move_elfs(positions, i % 4);
        if (positions == new_positions) {
            return i + 1;
        }
        positions = new_positions;
    }
    return -1;
}

