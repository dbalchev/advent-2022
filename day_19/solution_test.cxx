#include <gtest/gtest.h>

#include <day_19.h>

static day_19::ParsedData example_data = {
    {1, {
        {4, 0, 0, 0},
        {2, 0, 0, 0},
        {3, 14, 0, 0},
        {2, 0, 7, 0},
    }},
    {2, {
        {2, 0, 0, 0},
        {3, 0, 0, 0},
        {3, 8, 0, 0},
        {3, 0, 12, 0},
    }},
};

TEST(day_19, ParseInput) {
    EXPECT_EQ(example_data, day_19::parse_input("../../day_19/example.txt"));
}

TEST(day_19, SolvePart1) {
    EXPECT_EQ(33, day_19::solve_part_1(example_data));
}

TEST(day_19, SolvePart2) {
    EXPECT_EQ(31, day_19::solve_part_2(example_data));
}

