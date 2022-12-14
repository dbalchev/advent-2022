#include <gtest/gtest.h>

#include <day_14.h>

static day_14::ParsedData example_data = {
    {
        {498, 4},
        {498, 6},
        {496, 6},
    },
    {
        {503, 4},
        {502, 4},
        {502, 9},
        {494, 9},
    },
};

TEST(day_14, ParseInput) {
    EXPECT_EQ(example_data, day_14::parse_input("../../day_14/example.txt"));
}

TEST(day_14, SolvePart1) {
    EXPECT_EQ(24, day_14::solve_part_1(example_data));
}

TEST(day_14, SolvePart2) {
    EXPECT_EQ(31, day_14::solve_part_2(example_data));
}

