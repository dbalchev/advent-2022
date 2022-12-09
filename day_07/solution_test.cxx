#include <gtest/gtest.h>

#include <day_07.h>


std::ostream& operator<<(std::ostream& os, const day_07_ns::DirEntry& dir_entry) {
  return os 
    << "files=" 
    << testing::PrintToString(dir_entry.files) 
    << " directories=" 
    << testing::PrintToString(dir_entry.directories);
}

static day_07::ParsedData example_parsed_data = {
    {
        {"b.txt", 14848514},
        {"c.dat", 8504156},
    },
    {
        {"a", {
            {
                {"f", 29116},
                {"g", 2557},
                {"h.lst", 62596},
            },
            {
                {"e", {
                    {
                        {"i", 584}
                    },
                    {}
                }}
            }
        }},
        {"d", {
            {
                {"j", 4060174},
                {"d.log", 8033020},
                {"d.ext", 5626152},
                {"k", 7214296}
            },
            {

            }
        }}
    }
};

TEST(day_07, ParseInput) {
    auto parsed_data = day_07::parse_input("../../day_07/example.txt");
    EXPECT_EQ(example_parsed_data, parsed_data);
}

TEST(day_07, SolvePart1) {
    EXPECT_EQ(95437, day_07::solve_part_1(example_parsed_data));
}

TEST(day_07, SolvePart2) {
    EXPECT_EQ(24933642, day_07::solve_part_2(example_parsed_data));
}

