#include <gtest/gtest.h>

#include <day_21.h>
using namespace day_21_ns;

static day_21::ParsedData example_data = {
    {"root", OpMonkey {"pppw", '+', "sjmn"}},
    {"dbpl", int {5}},
    {"cczh", OpMonkey {"sllz", '+', "lgvd"}},
    {"zczc", int {2}},
    {"ptdq", OpMonkey {"humn", '-', "dvpt"}},
    {"dvpt", int {3}},
    {"lfqf", int {4}},
    {"humn", int {5}},
    {"ljgn", int {2}},
    {"sjmn", OpMonkey {"drzm", '*', "dbpl"}},
    {"sllz", int {4}},
    {"pppw", OpMonkey {"cczh", '/', "lfqf"}},
    {"lgvd", OpMonkey {"ljgn", '*', "ptdq"}},
    {"drzm", OpMonkey {"hmdt", '-', "zczc"}},
    {"hmdt", int {32}},
};

TEST(day_21, ParseInput) {
    EXPECT_EQ(example_data, day_21::parse_input("../../day_21/example.txt"));
}

TEST(day_21, SolvePart1) {
    EXPECT_EQ(152, day_21::solve_part_1(example_data));
}

TEST(day_21, SolvePart2) {
    EXPECT_EQ(301, day_21::solve_part_2(example_data));
}

