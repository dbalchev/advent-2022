#include <gtest/gtest.h>

#include <day_03.h>


TEST(day_03, ParseInput) {
    std::vector<std::pair<std::string, std::string> > expected = {
        {"vJrwpWtwJgWr", "hcsFMMfFFhFp"},
        {"jqHRNqRjqzjGDLGL", "rsFMfFZSrLrFZsSL"},
        {"PmmdzqPrV", "vPwwTWBwg"},
        {"wMqvLMZHhHMvwLH", "jbvcjnnSBnvTQFn"},
        {"ttgJtRGJ", "QctTZtZT"},
        {"CrZsJsPPZsGz", "wwsLwLmpwMDw"},
    };
    EXPECT_EQ(expected, day_03::parse_input("../../day_03/example.txt"));
}

TEST(day_03, SolvePart1) {
    std::vector<std::pair<std::string, std::string> > parsed_data = {
        {"vJrwpWtwJgWr", "hcsFMMfFFhFp"},
        {"jqHRNqRjqzjGDLGL", "rsFMfFZSrLrFZsSL"},
        {"PmmdzqPrV", "vPwwTWBwg"},
        {"wMqvLMZHhHMvwLH", "jbvcjnnSBnvTQFn"},
        {"ttgJtRGJ", "QctTZtZT"},
        {"CrZsJsPPZsGz", "wwsLwLmpwMDw"},
    };
    EXPECT_EQ(157, day_03::solve_part_1(parsed_data));
}

TEST(day_03, SolvePart2) {
    // EXPECT_EQ(31, day_03::solve_part_2(1));
}

