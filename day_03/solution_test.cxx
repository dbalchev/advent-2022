#include <gtest/gtest.h>

#include <day_03.h>


TEST(day_03, ParseInput) {
    day_03::ParsedData expected = {
        {"vJrwpWtwJgWrhcsFMMfFFhFp"},
        {"jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL"},
        {"PmmdzqPrVvPwwTWBwg"},
        {"wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn"},
        {"ttgJtRGJQctTZtZT"},
        {"CrZsJsPPZsGzwwsLwLmpwMDw"},
    };
    EXPECT_EQ(expected, day_03::parse_input("../../day_03/example.txt"));
}

TEST(day_03, SolvePart1) {
    day_03::ParsedData parsed_data = {
        {"vJrwpWtwJgWrhcsFMMfFFhFp"},
        {"jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL"},
        {"PmmdzqPrVvPwwTWBwg"},
        {"wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn"},
        {"ttgJtRGJQctTZtZT"},
        {"CrZsJsPPZsGzwwsLwLmpwMDw"},
    };
    EXPECT_EQ(157, day_03::solve_part_1(parsed_data));
}

TEST(day_03, SolvePart2) {
    day_03::ParsedData parsed_data = {
        {"vJrwpWtwJgWrhcsFMMfFFhFp"},
        {"jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL"},
        {"PmmdzqPrVvPwwTWBwg"},
        {"wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn"},
        {"ttgJtRGJQctTZtZT"},
        {"CrZsJsPPZsGzwwsLwLmpwMDw"},
    };
    EXPECT_EQ(70, day_03::solve_part_2(parsed_data));
}
