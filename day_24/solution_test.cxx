#include <gtest/gtest.h>

#include <day_24.h>

static day_24::ParsedData example_data = {
    {
        "#.######",
        "#......#",
        "#......#",
        "#......#",
        "#......#",
        "######.#",
    },
    {
        {1, 1, 0, 1},
        {1, 2, 0, 1},
        {1, 4, 0, -1},
        {1, 5, -1, 0},
        {1, 6, 0, -1},
        {2, 2, 0, -1},
        {2, 5, 0, -1},
        {2, 6, 0, -1},
        {3, 1, 0, 1},
        {3, 2, 1, 0},
        {3, 4, 0, 1},
        {3, 5, 0, -1},
        {3, 6, 0, 1},
        {4, 1, 0, -1},
        {4, 2, -1, 0},
        {4, 3, 1, 0},
        {4, 4, -1, 0},
        {4, 5, -1, 0},
        {4, 6, 0, 1},
    }
};

TEST(day_24, ParseInput) {
    EXPECT_EQ(example_data, day_24::parse_input("../../day_24/example.txt"));
}

TEST(day_24, SolvePart1) {
    EXPECT_EQ(18, day_24::solve_part_1(example_data));
}

TEST(day_24, SolvePart2) {
    EXPECT_EQ(54, day_24::solve_part_2(example_data));
}

