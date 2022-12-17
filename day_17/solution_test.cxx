#include <gtest/gtest.h>

#include <day_17.h>

static day_17::ParsedData example_data = ">>><<><>><<<>><>>><<<>>><<<><<<>><>><<>>";

TEST(day_17, ParseInput) {
    EXPECT_EQ(example_data, day_17::parse_input("../../day_17/example.txt"));
}

TEST(day_17, SolvePart1) {
    EXPECT_EQ(3068, day_17::solve_part_1(example_data));
}

TEST(day_17, SolvePart2) {
    EXPECT_EQ(
        1'514'285'714'288, 
        day_17::solve_part_2(example_data)
    );
}

