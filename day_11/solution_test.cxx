#include <gtest/gtest.h>

#include <day_11.h>

using namespace day_11_ns;

static std::vector<ParsedMonkey> example_input = {
    {
        {79, 98},
        {
            {"old", '*', "19"},
            23,
            {2, 3}
        }
    },
    {
        {54, 65, 75, 74},
        {
            {"old", '+', "6"},
            19,
            {2, 0}
        }
    },
    {
        {79, 60, 97},
        {
            {"old", '*', "old"},
            13,
            {1, 3}
        }
    },
    {
        {74},
        {
            {"old", '+', "3"},
            17,
            {0, 1}
        }
    }
};

TEST(day_11, ParseInput) {

    EXPECT_EQ(example_input, day_11::parse_input("../../day_11/example.txt"));
}

TEST(day_11, SolvePart1) {
    EXPECT_EQ(10605, day_11::solve_part_1(example_input));
}

TEST(day_11, SolvePart2) {
    EXPECT_EQ(2'713'310'158, day_11::solve_part_2(example_input));
}

