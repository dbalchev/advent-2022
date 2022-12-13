#include <gtest/gtest.h>

#include <day_13.h>

using namespace day_13_ns;


TEST(day_13, ParseInput) {
    EXPECT_EQ(8, day_13::parse_input("../../day_13/example.txt").size());
}

TEST(day_13, SolvePart1) {
    EXPECT_EQ(13, day_13::solve_part_1(day_13::parse_input("../../day_13/example.txt")));
}

TEST(day_13, SolvePart2) {
    EXPECT_EQ(140, day_13::solve_part_2(day_13::parse_input("../../day_13/example.txt")));
}

TEST(day_13, ParsePacket) {
    EXPECT_EQ(Packet{1}, day_13::parse_packet("1"));
    EXPECT_EQ(Packet{std::vector<Packet>({
        Packet{1}, Packet{1}, Packet{3}, Packet{1}, Packet{1}
    })}, day_13::parse_packet("[1,1,3,1,1]"));
    EXPECT_EQ(
        Packet{std::vector<Packet>({
            {std::vector<Packet>({{1}})},
            {43}
        })},
        day_13::parse_packet("[[1],43]")
    );
}
