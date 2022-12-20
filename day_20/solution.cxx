#include <iostream>
#include <iterator>
#include <algorithm>
#include <tuple>

#include <day_20.h>

day_20::ParsedData day_20::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    ParsedData result;
    std::copy(
        std::istream_iterator<int64_t>(fin),
        std::istream_iterator<int64_t>(),
        std::back_insert_iterator(result)
    );
    return result;
}

static int64_t solve(const day_20::ParsedData& original_input, int64_t multiplier, int num_mixes) {
    std::vector<std::tuple<int64_t, int64_t> > moved;
    for (int64_t i = 0; i < original_input.size(); ++i) {
        moved.push_back({i, original_input[i] * multiplier});
    }
    for (int mix_no = 0; mix_no < num_mixes; ++mix_no) {
        for (int64_t i = 0; i < original_input.size(); ++i) {
        auto number = original_input[i] * multiplier;
        if (number == 0) {
            continue;
        } else if (number > 0) {
            number = number % (original_input.size() - 1);
            auto iter = std::find_if(moved.begin(), moved.end(), [=](auto &x){
                return std::get<0>(x) == i;
            });
            day_20::move(moved.begin(), moved.end(), iter, number);

        } else {
            number = -(-number % (original_input.size() - 1));
            auto iter = std::find_if(moved.rbegin(), moved.rend(), [=](auto &x){
                return std::get<0>(x) == i;
            });
            day_20::move(moved.rbegin(), moved.rend(), iter, -number);
        }
    }
    }

    auto zero_position = std::find_if(moved.begin(), moved.end(), [](auto &x) {
        return std::get<1>(x) == 0;
    }) - moved.begin();
    int64_t sum = 0;
    for (int64_t i: {1000, 2000, 3000}) {
        auto pos = (zero_position + i) % moved.size();
        // std::cout << std::get<1>(moved[pos]) << std::endl;
        sum += std::get<1>(moved[pos]);
    }
    return sum;
}

day_20::ResultData day_20::solve_part_1(const ParsedData& parsed_data) {
    return solve(parsed_data, 1, 1);
}
day_20::ResultData day_20::solve_part_2(const ParsedData& parsed_data) {
    return solve(parsed_data, 811589153, 10) ;
}
