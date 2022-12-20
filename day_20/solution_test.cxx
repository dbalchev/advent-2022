#include <gtest/gtest.h>

#include <day_20.h>

static day_20::ParsedData example_data = {
    1,
    2,
    -3,
    3,
    -2,
    0,
    4,
};

TEST(day_20, ParseInput) {
    EXPECT_EQ(example_data, day_20::parse_input("../../day_20/example.txt"));
}


TEST(day_20, one_move_forward) {
    std::vector<int> starting_array = {
        1, 2, -3, 0, 3, 4, -2
    };
    std::vector<int> expected = {
        1, 2, -3, 4, 0, 3, -2
    };
    day_20::move(
        starting_array.begin(), 
        starting_array.end(),
        std::find(starting_array.begin(), starting_array.end(), 4),
        4
    );
    EXPECT_EQ(expected, starting_array);
}


TEST(day_20, one_move_back) {
    std::vector<int> starting_array = {
        4, -2, 5, 6, 7, 8, 9
    };
    std::vector<int> expected = {
        4, 5, 6, 7, 8, -2, 9
    };
    day_20::move(
        starting_array.rbegin(), 
        starting_array.rend(),
        std::find(starting_array.rbegin(), starting_array.rend(), -2),
        2
    );
    EXPECT_EQ(expected, starting_array);
}

TEST(day_20, SolvePart1) {
    EXPECT_EQ(3, day_20::solve_part_1(example_data));
}

TEST(day_20, SolvePart2) {
    EXPECT_EQ(1623178306, day_20::solve_part_2(example_data));
}

