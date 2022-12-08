#include <gtest/gtest.h>

#include <day_08.h>

static day_08::ParsedData example_data = {
    "30373",
    "25512",
    "65332",
    "33549",
    "35390"
};

TEST(day_08, ParseInput) {
    EXPECT_EQ(example_data, day_08::parse_input("../../day_08/example.txt"));
}


TEST(day_08, ComputeLeftVisibilityMask) {
    std::vector<std::vector<bool> > expected_visibility = {
        {true, false, false, true, false},
        {true, true, false, false, false},
        {true, false, false, false, false},
        {true, false, true, false, true},
        {true, true, false, true, false},
    };
    EXPECT_EQ(
        expected_visibility, 
        day_08::compute_left_visibility_mask(example_data)
    );
}

TEST(day_08, ComputeTopVisibilityMask) {
    std::vector<std::vector<bool> > expected_visibility = {
        {true, true, true, true, true},
        {false, true, true, false, false},
        {true, false, false, false, false},
        {false, false, false, false, true},
        {false, false, false, true, false},
    };
    EXPECT_EQ(
        expected_visibility, 
        day_08::compute_top_visibility_mask(example_data)
    );
}

TEST(day_08, ComputeLeftVisibilityDistances) {
    std::vector<std::vector<int> > expected_visibility = {
        {0, 1, 2, 3, 1},
        {0, 1, 1, 1, 2},
        {0, 1, 1, 1, 1},
        {0, 1, 2, 1, 4},
        {0, 1, 1, 3, 1}
    };
    EXPECT_EQ(
        expected_visibility, 
        day_08::compute_left_visibility_distances(example_data)
    );
}

TEST(day_08, ComputeTopVisibilityDistances) {
    std::vector<std::vector<int> > expected_visibility = {
        {0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
        {2, 1, 1, 2, 1},
        {1, 1, 2, 3, 3},
        {1, 2, 1, 4, 1}
    };
    EXPECT_EQ(
        expected_visibility, 
        day_08::compute_top_visibility_distances(example_data)
    );
}

TEST(day_08, SolvePart1) {
    EXPECT_EQ(21, day_08::solve_part_1(example_data));
}

TEST(day_08, SolvePart2) {
    EXPECT_EQ(8, day_08::solve_part_2(example_data));
}

