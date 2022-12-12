#include <gtest/gtest.h>

#include <day_12.h>

static day_12::ParsedData example_input = {
    "Sabqponm",
    "abcryxxl",
    "accszExk",
    "acctuvwj",
    "abdefghi",
};

TEST(day_12, ParseInput) {

    EXPECT_EQ(example_input, day_12::parse_input("../../day_12/example.txt"));
}

TEST(day_12, SolvePart1) {
    EXPECT_EQ(31, day_12::solve_part_1(example_input));
}

TEST(day_12, SolvePart2) {
    EXPECT_EQ(29, day_12::solve_part_2(example_input));
}

