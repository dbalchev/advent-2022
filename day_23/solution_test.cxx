#include <gtest/gtest.h>

#include <day_23.h>

static day_23::ParsedData example_data = {
    {0, 4},
    {1, 2},
    {1, 3},
    {1, 4},
    {1, 6},
    {2, 0},
    {2, 4},
    {2, 6},
    {3, 1},
    {3, 5},
    {3, 6},
    {4, 0},
    {4, 2},
    {4, 3},
    {4, 4},
    {5, 0},
    {5, 1},
    {5, 3},
    {5, 5},
    {5, 6},
    {6, 1},
    {6, 4},
};

TEST(day_23, ParseInput) {
    EXPECT_EQ(example_data, day_23::parse_input("../../day_23/example.txt"));
}

TEST(day_23, SolvePart1) {
    EXPECT_EQ(110, day_23::solve_part_1(example_data));
}

TEST(day_23, SolvePart2) {
    EXPECT_EQ(20, day_23::solve_part_2(example_data));
}

