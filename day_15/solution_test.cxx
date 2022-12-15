#include <gtest/gtest.h>

#include <day_15.h>

static day_15::ParsedData example_data = {
    {10, 20},
    {
        {{2, 18}, {-2, 15}},
        {{9, 16}, {10, 16}},
        {{13, 2}, {15, 3}},
        {{12, 14}, {10, 16}},
        {{10, 20}, {10, 16}},
        {{14, 17}, {10, 16}},
        {{8, 7}, {2, 10}},
        {{2, 0}, {2, 10}},
        {{0, 11}, {2, 10}},
        {{20, 14}, {25, 17}},
        {{17, 20}, {21, 22}},
        {{16, 7}, {15, 3}},
        {{14, 3}, {15, 3}},
        {{20, 1}, {15, 3}},
    }
};

TEST(day_15, ParseInput) {
    EXPECT_EQ(example_data, day_15::parse_input("../../day_15/example.txt"));
}

TEST(day_15, SolvePart1) {
    EXPECT_EQ(26, day_15::solve_part_1(example_data));
}

TEST(day_15, SolvePart2) {
    EXPECT_EQ(56000011, day_15::solve_part_2(example_data));
}

