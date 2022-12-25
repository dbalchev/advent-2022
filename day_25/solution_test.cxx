#include <gtest/gtest.h>

#include <tuple>
#include <day_25.h>

static day_25::ParsedData example_data = {
    "1=-0-2",
    "12111",
    "2=0=",
    "21",
    "2=01",
    "111",
    "20012",
    "112",
    "1=-1=",
    "1-12",
    "12",
    "1=",
    "122",
};

TEST(day_25, ParseInput) {
    EXPECT_EQ(example_data, day_25::parse_input("../../day_25/example.txt"));
}

TEST(day_25, SolvePart1) {
    EXPECT_EQ("2=-1=0", day_25::solve_part_1(example_data));
}

const static std::vector<std::tuple<int64_t, std::string> > test_values = {
{        1,              "1"},
{        2,              "2"},
{        3,             "1="},
{        4,             "1-"},
{        5,             "10"},
{        6,             "11"},
{        7,             "12"},
{        8,             "2="},
{        9,             "2-"},
{       10,             "20"},
{       15,            "1=0"},
{       20,            "1-0"},
{     2022,         "1=11-2"},
{    12345,        "1-0---0"},
{ 314159265,  "1121-1110-1=0"},

};

TEST(day_25, parse_snafu) {
    for (auto [i, snafu]: test_values) {
        ASSERT_EQ(i, day_25::parse_snafu(snafu));
    }
}


TEST(day_25, snafufy) {
    for (auto [i, snafu]: test_values) {
        ASSERT_EQ(snafu, day_25::snafufy(i));
    }
}