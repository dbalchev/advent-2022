#include <gtest/gtest.h>

#include <day_09.h>

using namespace day_09_ns;

static std::vector<Instruction> example_input = {
    {'R', 4},
    {'U', 4},
    {'L', 3},
    {'D', 1},
    {'R', 4},
    {'D', 1},
    {'L', 5},
    {'R', 2}
};

TEST(day_09, ParseInput) {

    EXPECT_EQ(example_input, day_09::parse_input("../../day_09/example.txt"));
}

TEST(day_09, SolvePart1) {
    EXPECT_EQ(13, day_09::solve_part_1(example_input));
}

TEST(day_09, SolvePart2) {
    EXPECT_EQ(1, day_09::solve_part_2(example_input));
}

TEST(day_09, SolvePart2_Bigger) {
    std::vector<Instruction> bigger_input = {
        {'R', 5},
        {'U', 8},
        {'L', 8},
        {'D', 3},
        {'R', 17},
        {'D', 10},
        {'L', 25},
        {'U', 20},
    };
    EXPECT_EQ(36, day_09::solve_part_2(bigger_input));
}
