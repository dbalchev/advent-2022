#include <gtest/gtest.h>

#include <day_18.h>

static day_18::ParsedData example_data = {
    {2, 2, 2},
    {1, 2, 2},
    {3, 2, 2},
    {2, 1, 2},
    {2, 3, 2},
    {2, 2, 1},
    {2, 2, 3},
    {2, 2, 4},
    {2, 2, 6},
    {1, 2, 5},
    {3, 2, 5},
    {2, 1, 5},
    {2, 3, 5},
};

TEST(day_18, ParseInput) {
    EXPECT_EQ(example_data, day_18::parse_input("../../day_18/example.txt"));
}

TEST(day_18, SolvePart1) {
    EXPECT_EQ(64, day_18::solve_part_1(example_data));
}

TEST(day_18, SolvePart2) {
    EXPECT_EQ(58, day_18::solve_part_2(example_data));
}

