#include <gtest/gtest.h>

#include <day_22.h>

static day_22::ParsedData example_data = {
    {
        "        ...#    ",
        "        .#..    ",
        "        #...    ",
        "        ....    ",
        "...#.......#    ",
        "........#...    ",
        "..#....#....    ",
        "..........#.    ",
        "        ...#....",
        "        .....#..",
        "        .#......",
        "        ......#.",
    }, 
    {10, -1, 5, -3, 5, -1, 10, -3, 4, -1, 5, -3, 5}
};

TEST(day_22, ParseInput) {
    EXPECT_EQ(example_data, day_22::parse_input("../../day_22/example.txt"));
}

TEST(day_22, SolvePart1) {
    EXPECT_EQ(6032, day_22::solve_part_1(example_data));
}

TEST(day_22, SolvePart2) {
    EXPECT_EQ(5031, day_22::solve_part_2(example_data));
}

