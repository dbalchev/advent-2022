#include <iostream>

#include <day_09.h>
#include <unordered_set>

using namespace day_09_ns;

day_09::ParsedData day_09::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    ParsedData result;
    while (fin) {
        char c;
        int n;
        fin >> c >> n;
        if (!fin) {
            break;
        }
        result.push_back({c, n});
    }
    return result;
}

static Position move_head(Position head, char c) {
    auto [x, y] = head;
    switch (c) {
    case 'U':
        return {x, y + 1};
    case 'R':
        return {x + 1, y};
    case 'D':
        return {x, y - 1};
    case 'L':
        return {x - 1, y};
    default:
        throw std::runtime_error(std::string("Unknown direction ") + c);
    }
}

static int single_d_move(int x) {
    if (x == 0) {
        return 0;
    }
    if (x > 0) {
        return 1;
    }
    return -1;
}



static Position update_tail(
    Position head,
    Position tail
) {
    auto [hx, hy] = head;
    auto [tx, ty] = tail;
    auto dx = hx - tx;
    auto dy = hy - ty;

    if (abs(dx) < 2 && abs(dy) < 2) {
        return {tx, ty};
    }
    dx = single_d_move(dx);
    dy = single_d_move(dy);
    tx += dx;
    ty += dy;
    return {tx, ty};
}

template<>
struct std::hash<Position> {
    std::size_t operator()(const Position& p) const noexcept {
        auto [x, y] = p;
        return std::hash<int>{}(x) * 17 + std::hash<int>{}(y);
    }
};

day_09::ResultData day_09::solve_part_1(const ParsedData& parsed_data) {
    Position head = {0, 0}, tail = {0, 0};
    std::unordered_set<Position> tail_history = {tail};
    for (auto& [direction, step_count]: parsed_data) {
        for (int i = 0; i < step_count; ++i) {
            head = move_head(head, direction);
            tail = update_tail(head, tail);
            tail_history.insert(tail);
        }
    }
    return tail_history.size();
}
day_09::ResultData day_09::solve_part_2(const ParsedData& parsed_data) {
    std::vector<Position> rope(10, {0, 0});
    std::unordered_set<Position> tail_history = {rope.back()};
    for (auto& [direction, step_count]: parsed_data) {
        for (int i = 0; i < step_count; ++i) {
            auto& head = rope.front();
            head = move_head(head, direction);
            for (int j = 1; j < rope.size(); ++j) {
                rope[j] = update_tail(rope[j-1], rope[j]);
            }
            tail_history.insert(rope.back());
        }
    }
    return tail_history.size();
}
