#include <gtest/gtest.h>

#include <day_02.h>

using namespace day_02;

TEST(day_02, ParseInput) {
    std::vector<std::pair<int, int> > expected = {
        {0, 1},
        {1, 0},
        {2, 2},
    };
    EXPECT_EQ(expected, parse_input("../../day_02/example.txt"));
}

TEST(day_02, ScorePart1) {
    std::vector<std::pair<int, int> > plan = {
        {0, 1},
        {1, 0},
        {2, 2},
    };
    EXPECT_EQ(15, score_part_1(plan));
}

TEST(day_02, ScorePart2) {
    std::vector<std::pair<int, int> > plan = {
        {0, 1},
        {1, 0},
        {2, 2},
    };
    EXPECT_EQ(12, score_part_2(plan));
}