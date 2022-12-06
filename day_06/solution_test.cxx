#include <gtest/gtest.h>

#include <day_06.h>


TEST(day_06, ParseInput) {

    EXPECT_EQ(
        "mjqjpqmgbljsphdztnvjfqwrcgsmlb", 
        day_06::parse_input("../../day_06/example.txt")
    );
}

TEST(day_06, SolvePart1_0) {
    EXPECT_EQ(7, day_06::solve_part_1("mjqjpqmgbljsphdztnvjfqwrcgsmlb"));
}

TEST(day_06, SolvePart1_1) {
    EXPECT_EQ(5, day_06::solve_part_1("bvwbjplbgvbhsrlpgdmjqwftvncz"));
}

TEST(day_06, SolvePart1_2) {
    EXPECT_EQ(6, day_06::solve_part_1("nppdvjthqldpwncqszvftbrmjlhg"));
}

TEST(day_06, SolvePart1_3) {
    EXPECT_EQ(10, day_06::solve_part_1("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg"));
}

TEST(day_06, SolvePart1_4) {
    EXPECT_EQ(11, day_06::solve_part_1("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"));
}

TEST(day_06, SolvePart2_0) {
    EXPECT_EQ(19, day_06::solve_part_2("mjqjpqmgbljsphdztnvjfqwrcgsmlb"));
}

TEST(day_06, SolvePart2_1) {
    EXPECT_EQ(23, day_06::solve_part_2("bvwbjplbgvbhsrlpgdmjqwftvncz"));
}

TEST(day_06, SolvePart2_2) {
    EXPECT_EQ(23, day_06::solve_part_2("nppdvjthqldpwncqszvftbrmjlhg"));
}

TEST(day_06, SolvePart2_3) {
    EXPECT_EQ(29, day_06::solve_part_2("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg"));
}

TEST(day_06, SolvePart2_4) {
    EXPECT_EQ(26, day_06::solve_part_2("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"));
}
