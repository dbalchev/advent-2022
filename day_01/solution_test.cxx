#include <gtest/gtest.h>

#include <day_01.h>

using namespace day_01;

TEST(day_01, ReadTest) {
    std::vector<std::vector<int> > expected = {
        {1'000, 2'000, 3'000},
        {4'000},
        {5'000, 6'000},
        {7'000, 8'000, 9'000},
        {10'000},
    };
    EXPECT_EQ(expected, read_from_file("../../day_01/example.txt"));
}

TEST(day_01, Top3SumTest) {
    std::vector<int> input = {
        6'000,
        4'000,
        11'000,
        24'000,
        10'000,
    };
    EXPECT_EQ(45'000, compute_top3_sum(input));
}

