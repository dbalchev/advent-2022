#include <gtest/gtest.h>

#include <day_00.h>

static day_00::ParsedData example_data = 1;

TEST(day_00, ParseInput) {
    EXPECT_EQ(example_data, day_00::parse_input("../../day_00/example.txt"));
}

TEST(day_00, SolvePart1) {
    EXPECT_EQ(21, day_00::solve_part_1(example_data));
}

TEST(day_00, SolvePart2) {
    EXPECT_EQ(31, day_00::solve_part_2(example_data));
}
