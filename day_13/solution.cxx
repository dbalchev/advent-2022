#include <iostream>

#include <day_13.h>

using namespace day_13_ns;

day_13::ParsedData day_13::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    ParsedData result;
    while (fin) {
        std::string line;
        std::getline(fin, line);
        if (!line.length()) {
            break;
        }
        auto packet_1 = parse_packet(line);
        std::getline(fin, line);
        auto packet_2 = parse_packet(line);
        std::getline(fin, line);
        if (line.length()) {
            throw std::runtime_error("last line should be empty " + line);
        }
        result.push_back({packet_1, packet_2});
    }
    return result;
}

static std::vector<Packet> to_packet_list(const Packet& x) {
    if (x.index() == 0) {
        return {x};
    }
    return std::get<1>(x);
}

static int compare(const Packet& lh, const Packet &rh) {
    if (lh.index() == 0 && rh.index() == 0) {
        auto ln = std::get<0>(lh);
        auto rn = std::get<0>(rh);
        return ln - rn;
    }
    auto ll = to_packet_list(lh);
    auto rl = to_packet_list(rh);

    auto max_len = std::max(ll.size(), rl.size());
    for (int i = 0; i < max_len; ++i) {
        if (i >= ll.size()) {
            return -1;
        }
        if (i >= rl.size()) {
            return 1;
        }
        int c = compare(ll[i], rl[i]);
        if (c != 0) {
            return c;
        }
    }
    return 0;
}

day_13::ResultData day_13::solve_part_1(const ParsedData& parsed_data) {
    int result = 0;
    for (int i = 0; i < parsed_data.size(); ++i) {
        auto &[lh, rh] = parsed_data[i];
        auto c = compare(lh, rh);
        if (c < 0) {
            result += i + 1;
        }
    }
    return result;
}

static void print(day_13::Packet x) {
    if (x.index() == 0) {
        std::cout << std::get<0>(x);
        return;
    }
    auto &v = std::get<1>(x);
    std::cout << "[";
    for (auto &p: v) {
        print(p);
        std::cout << ",";
    }
    std::cout << "]";
}

day_13::ResultData day_13::solve_part_2(const ParsedData& parsed_data) {
    Packet divider_1 = {
        std::vector<Packet>({
            Packet{
                std::vector<Packet>({
                    {2}
                })
            }
        })
    };
    Packet divider_2 = {
        std::vector<Packet>({
            Packet{
                std::vector<Packet>({
                    {6}
                })
            }
        })
    };
    std::vector<Packet> all_packets = {divider_1, divider_2};
    for (auto &[lh, rh]: parsed_data) {
        all_packets.push_back(lh);
        all_packets.push_back(rh);
    }
    auto comparator = [](const auto &lh, const auto &rh) {
        return compare(lh, rh) < 0;
    };
    std::sort(all_packets.begin(), all_packets.end(), comparator);
    // for (auto &p: all_packets){
    //     print(p);
    //     std::cout << std::endl;
    // }
    // print(divider_1);
    // std::cout << std::endl;
    // print(divider_2);
    // std::cout << std::endl;
    auto divider_1_it = std::find(all_packets.begin(), all_packets.end(), divider_1);
    auto divider_2_it = std::find(all_packets.begin(), all_packets.end(), divider_2);
    // std::cout << divider_1_it - all_packets.begin() << " " <<  divider_2_it - all_packets.begin() << std::endl;
    return (1 + divider_1_it - all_packets.begin()) * (1 + divider_2_it - all_packets.begin());
}

std::tuple<Packet, std::string::const_iterator> day_13::parse_packet(
    std::string::const_iterator begin, std::string::const_iterator end
) {
    static const std::string digits = "0123456789";

    if (begin == end) {
        throw std::runtime_error("empty range");
    }

    if (isnumber(*begin)) {
        std::string::const_iterator number_end = begin;
        while (number_end != end && isnumber(*number_end)) {
            number_end ++;
        }
        return {Packet{std::stoi(std::string(begin, number_end))}, number_end};
    }
    if (*begin != '[') {
        throw std::runtime_error(std::string("Wrong first char ") + (char)*begin);
    }
    std::vector<Packet> result;
    while (*begin != ']') {
        begin++;
        if (*begin == ']') {
            begin++;
            break;
        }
        auto [packet, new_begin] = parse_packet(begin, end);
        result.push_back(std::move(packet));

        begin = new_begin;
        if (*begin == ']') {
            begin++;
            break;
        }
        if (*begin != ',') {
            throw std::runtime_error("expected a coma");
        }
    }
    return {Packet{std::move(result)}, begin};
}