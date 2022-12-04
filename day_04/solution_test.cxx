#include <gtest/gtest.h>

#include <day_04.h>

static day_04::ParsedData example_data = {
    {{2, 4}, {6, 8}},
    {{2, 3}, {4, 5}},
    {{5, 7}, {7, 9}},
    {{2, 8}, {3, 7}},
    {{6, 6}, {4, 6}},
    {{2, 6}, {4, 8}},
};

TEST(day_04, ParseInput) {
    
    EXPECT_EQ(example_data, day_04::parse_input("../../day_04/example.txt"));
}

TEST(day_04, ParseInput2Digit) {
    day_04::ParsedData parsed_data = {
        {{2, 14}, {6, 8}},
        {{32, 3}, {4, 5}},
        {{5, 7}, {67, 9}},
        {{2, 8}, {3, 7}},
        {{6, 6}, {4, 69}},
        {{12, 26}, {34, 48}},
    };
    EXPECT_EQ(parsed_data, day_04::parse_input("../../day_04/test-2-digit.txt"));
}

TEST(day_04, SolvePart1) {
    EXPECT_EQ(2, day_04::solve_part_1(example_data));
}

TEST(day_04, SolvePart2) {
    EXPECT_EQ(4, day_04::solve_part_2(example_data));
}

TEST(day_04, IsContained) {
    EXPECT_TRUE(day_04::is_contained({1, 2}, {1, 2}));
    EXPECT_FALSE(day_04::is_contained({1, 3}, {4, 5}));
    EXPECT_FALSE(day_04::is_contained({4, 5}, {1, 3}));
    EXPECT_FALSE(day_04::is_contained({1, 4}, {3, 5}));
    EXPECT_FALSE(day_04::is_contained({5, 7}, {7, 9}));
    EXPECT_FALSE(day_04::is_contained({7, 9}, {5, 7}));

    EXPECT_TRUE(day_04::is_contained({2, 8}, {3, 7}));
    EXPECT_TRUE(day_04::is_contained({6, 6}, {4, 6}));
    EXPECT_FALSE(day_04::is_contained({2, 6}, {4, 8}));

    EXPECT_TRUE(day_04::is_contained({1, 4}, {3, 4}));
    EXPECT_TRUE(day_04::is_contained({1, 4}, {2, 3}));

    //Reproduce bugs
    EXPECT_TRUE(day_04::is_contained({6, 6}, {4, 7}));
    EXPECT_TRUE(day_04::is_contained({6, 6}, {6, 8}));

}