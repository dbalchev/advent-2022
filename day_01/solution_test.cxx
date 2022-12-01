#include <gtest/gtest.h>

#include <day_01.h>

TEST(day_01, ReadTest) {
    std::vector<std::vector<int> > expected = {
        {1000, 2000, 3000},
        {4000},
        {5000, 6000},
        {7000, 8000, 9000},
        {10000},
    };
    EXPECT_EQ(expected, read_day01_from_file("../../day_01/example.txt"));
}

