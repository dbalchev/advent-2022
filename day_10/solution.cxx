#include <iostream>

#include <day_10.h>
#include <range/v3/view.hpp>

using namespace day_10_ns;

day_10::ParsedData day_10::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    ParsedData result;
    while(fin) {
        std::string instruction;
        int arg = 0;
        fin >> instruction;
        if (!fin) {
            break;
        }
        if (instruction == "addx") {
            fin >> arg;
            result.push_back({Instruction::ADDX, arg});
        } else if (instruction == "noop") {
            result.push_back({Instruction::NOOP, arg});
        } else {
            throw std::runtime_error("Unknown instruction " + instruction);
        }
    }
    return result;
}

static std::vector<int> compute_cycle_history(const day_10::ParsedData &parsed_data) {
    auto cycle_data = parsed_data
         | ranges::views::transform([](const auto& instruction) -> std::pair<int, int> {
            auto [opcode, arg] = instruction;

            switch (opcode) {
                case Instruction::ADDX:
                    return {2, arg};
                case Instruction::NOOP:
                    return {1, 0};
                default:
                    throw std::runtime_error("unknown instruction");
            }
         })
         | ranges::views::partial_sum([](std::pair<int, int> lh, std::pair<int, int> rh) -> std::pair<int, int> {
            auto [lt, la] = lh;
            auto [rt, ra] = rh;
            return {lt + rt, la + ra};
        })
         | ranges::views::transform([](std::pair<int, int> p) -> std::pair<int, int> {
            auto [t, r] = p;
            return {t, r + 1};
         })
         | ranges::to<std::vector>();
    std::vector<int> cycle_history = {1};
    for (auto [i, x]: cycle_data) {
        while (cycle_history.size() < i) {
            cycle_history.push_back(cycle_history.back());
        }
        cycle_history.push_back(x);
    }
    return cycle_history;
}

day_10::ResultData day_10::solve_part_1(const ParsedData& parsed_data) {
    auto cycle_history = compute_cycle_history(parsed_data);
    auto result = 20 * cycle_history[19] + 60 * cycle_history[59] + 100 * cycle_history[99] +
        140 * cycle_history[139] + 180 * cycle_history[179] + 220 * cycle_history[219];
    return std::to_string(result);
}
day_10::ResultData day_10::solve_part_2(const ParsedData& parsed_data) {
    auto cycle_history = compute_cycle_history(parsed_data);
    auto render = ranges::views::ints(0, 240)
        | ranges::views::transform([&](int cycle) -> char {
            auto cursor_pos = cycle % 40;
            auto sprite_center = cycle_history[cycle];
            return (sprite_center - 1 <= cursor_pos && cursor_pos <= sprite_center + 1) ? '#' : '.';
        })
        | ranges::views::chunk(40)
        | ranges::views::join('\n')
        | ranges::to<std::string>();
    return "\n" + render + "\n";
}
