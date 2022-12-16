#include <gtest/gtest.h>

#include <day_16.h>

static day_16::ParsedData example_data = {
    {0, {3, 8, 1}},
    {13, {2, 0}},
    {2, {3, 1}},
    {20, {2, 0, 4}},
    {3, {5, 3}},
    {0, {4, 6}},
    {0, {5, 7}},
    {22, {6}},
    {0, {0, 9}},
    {21, {8}},

};

TEST(day_16, ParseInput) {
    EXPECT_EQ(example_data, day_16::parse_input("../../day_16/example.txt"));
}

TEST(day_16, SolvePart1) {
    EXPECT_EQ(1651, day_16::solve_part_1(example_data));
}

TEST(day_16, SolvePart2) {
    EXPECT_EQ(1707, day_16::solve_part_2(example_data));
}

