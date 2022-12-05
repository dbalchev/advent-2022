#include <gtest/gtest.h>

#include <day_05.h>


static day_05::ParsedData parsed_example = {
    {
        {'Z', 'N'},
        {'M', 'C', 'D'},
        {'P'}
    },
    {
        {1, 2, 1},
        {3, 1, 3},
        {2, 2, 1},
        {1, 1, 2},
    }
};

TEST(day_05, ParseInput) {
    EXPECT_EQ(parsed_example, day_05::parse_input("../../day_05/example.txt"));
}

TEST(day_05, SolvePart1) {
    EXPECT_EQ("CMZ", day_05::solve_part_1(parsed_example));
}

TEST(day_05, SolvePart2) {
    EXPECT_EQ("MCD", day_05::solve_part_2(parsed_example));
}

