#pragma once

#include <SolutionBase.h>
#include <variant>
#include <vector>
#include <tuple>

namespace day_13_ns {
    struct Packet: std::variant<
        int,
        std::vector<Packet>
    >{
        
    };
}

class day_13: public SolutionBase<
    day_13, 
    std::vector<std::tuple<day_13_ns::Packet, day_13_ns::Packet> > 
>{
public:
    typedef day_13_ns::Packet Packet;

    static ParsedData parse_input(const char* filename);

    static ResultData solve_part_1(const ParsedData& parsed_data);

    static ResultData solve_part_2(const ParsedData& parsed_data);

    static Packet parse_packet(const std::string& s) {
        auto [result, end] = parse_packet(s.begin(), s.end());

        if (end != s.end()) {
            throw std::runtime_error("Didn't finish parsing");
        }
        return result;
    }
    static std::tuple<Packet, std::string::const_iterator> parse_packet(
        std::string::const_iterator begin, std::string::const_iterator end
    );
};

