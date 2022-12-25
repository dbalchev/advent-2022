#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>

#include <range/v3/view.hpp>
#include <range/v3/numeric.hpp>

#include <day_25.h>

day_25::ParsedData day_25::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    std::vector<std::string> result;
    std::copy(
        std::istream_iterator<std::string>(fin),
        std::istream_iterator<std::string>(),
        std::back_insert_iterator(result)
    );
    return result;
}


static int from_digit(char c) {
    int d;
    switch(c) {
        case '=':
            d = -2;
            break;
        case '-':
            d = -1;
            break;
        case '0':
        case '1':
        case '2':
            d = c - '0';
            break;
        default:
            throw std::runtime_error("unknown digit");
    }
    return d;
}

static char to_digit(int r) {
    char c;
    switch (r) {
        case -2:
            c = '=';
            break;
        case -1:
            c = '-';
            break;
        case 0:
        case 1:
        case 2:
            c = '0' + r;
            break;
        default:
            throw std::runtime_error("unknown remainder " + std::to_string(r));
    }
    return c;
} 

int64_t day_25::parse_snafu(const std::string &s) {
    int64_t r = 0;
    for (auto c: s) {
        int64_t d = from_digit(c);

        if (r < 0) {
            throw std::runtime_error("overflow!");
        }
        r = 5 * r + d;
    }
    return r;
}

std::string day_25::snafufy(int64_t n) {
    std::string result;
    while (n > 0) {
        int64_t q = n / 5;
        int64_t r = n % 5;

        if (r > 2) {
            r -= 5;
            q += 1;
        } 
        auto c = to_digit(r);
        n = q;
        result.push_back(c);
    }
    std::reverse(result.begin(), result.end());
    return result;
}


std::string snafu_add(const std::string &lh, const std::string &rh) {
    std::string result;
    int carry = 0;
    auto lhs = lh.size();
    auto rhs = rh.size();
    for (size_t i = 0; i < lhs || i < rhs; ++i) {
        int lhd =  i < lhs ? from_digit(lh[lhs - i - 1]) : 0;
        int rhd =  i < rhs ? from_digit(rh[rhs - i - 1]) : 0;

        int d = lhd + rhd + carry;
        
        if (d < -2) {
            carry = -1;
            d += 5;
        } else if (d > 2) {
            carry = 1;
            d -= 5;
        } else {
            carry = 0;
        }
        result.push_back(to_digit(d));
    }
    if (carry != 0) {
        result.push_back(to_digit(carry));
    }
    std::reverse(result.begin(), result.end());
    return result;
}

day_25::ResultData day_25::solve_part_1(const ParsedData& parsed_data) {
    return ranges::accumulate(
        parsed_data,
        std::string("0"),
        snafu_add
    );
}
day_25::ResultData day_25::solve_part_2(const ParsedData& parsed_data) {
    return "";
}

