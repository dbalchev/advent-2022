#include <iostream>

#include <day_11.h>

#include <regex>
#include <algorithm>
#include <range/v3/view.hpp>
#include <range/v3/numeric/accumulate.hpp>

using namespace day_11_ns;

static ParsedMonkey read_monkey(const std::vector<std::string> &lines) {
    static const std::string line_1_prefix = "  Starting items: ";
    static const std::string line_2_prefix = "  Operation: new = ";
    static const std::string line_3_prefix = "  Test: divisible by ";
    static const std::string line_4_prefix = "    If true: throw to monkey ";
    static const std::string line_5_prefix = "    If false: throw to monkey ";
    if (lines[1].substr(0, line_1_prefix.length()) != line_1_prefix) {
        throw std::runtime_error("Incorrect prefix \"" + lines[1]);
    }
    std::string split_delimiter = ", ";
    std::string line_1_suffix = lines[1].substr(line_1_prefix.length());
    auto starting_items = line_1_suffix
        | ranges::views::split(std::string(", "))
        | ranges::views::transform([](auto s) -> int64_t {
            return std::stoi(s | ranges::to<std::string>());
        })
        | ranges::to<std::vector>();
    if (lines[2].substr(0, line_2_prefix.length()) != line_2_prefix) {
        throw std::runtime_error("Incorrect prefix \"" + lines[2]);
    }
    std::string line_2_suffix = lines[2].substr(line_2_prefix.length());
    auto operation_terms = line_2_suffix
        | ranges::views::split(std::string(" "))
        | ranges::views::transform([](auto s) -> std::string {
            return (s | ranges::to<std::string>());
        })
        | ranges::to<std::vector>();
    if (lines[3].substr(0, line_3_prefix.length()) != line_3_prefix) {
        throw std::runtime_error("Incorrect prefix \"" + lines[3]);
    }
    int divisible_by = std::stoi(lines[3].substr(line_3_prefix.length()));
    if (lines[4].substr(0, line_4_prefix.length()) != line_4_prefix) {
        throw std::runtime_error("Incorrect prefix \"" + lines[4]);
    }
    int true_monkey = std::stoi(lines[4].substr(line_4_prefix.length()));
    if (lines[5].substr(0, line_5_prefix.length()) != line_5_prefix) {
        throw std::runtime_error("Incorrect prefix \"" + lines[5]);
    }
    int false_monkey = std::stoi(lines[5].substr(line_5_prefix.length()));
    return {
        std::move(starting_items),
        {
            {std::move(operation_terms[0]), operation_terms[1][0], std::move(operation_terms[2])},
            divisible_by,
            {true_monkey, false_monkey}
        }
    };
}

day_11::ParsedData day_11::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    std::vector<ParsedMonkey> result;
    while (fin){
        auto lines = ranges::views::ints(0, 7)
            | ranges::views::transform([&fin](int _) -> std::string {
                std::string line;
                std::getline(fin, line);
                return line;
            })
            | ranges::to<std::vector>();
        if (!lines[0].length()) {
            break;
        }
        if (lines[0] != "Monkey " + std::to_string(result.size()) + ":") {
            throw std::runtime_error("First line is incorrect: " + lines[0]);
        }
        result.push_back(read_monkey(lines));
    }
    // {

    return result;
}

static int64_t compute_expression(const std::string &term, int64_t old_worry) {
    if (term == "old") {
        return old_worry;
    }
    return std::stoi(term);
}

static std::pair<int, int64_t> find_next_monkey_and_worry(
    const MonkeyTransition& transition, int64_t old_worry, int worry_divisor, int64_t modulo
    ) {
    auto &[expression, divisor, pass_to] = transition;
    auto &[true_monkey, false_monkey] = pass_to;
    auto &[lt, op, rt] = expression;

    int64_t lh = compute_expression(lt, old_worry);
    int64_t rh = compute_expression(rt, old_worry);
    int64_t r;
    switch(op) {
        case '+':
            r = lh + rh;
            break;
        case '*':
            r = lh * rh;
            break;
        default:
            throw std::runtime_error(std::string("Unknown op ") + op);
    }
    r /= worry_divisor;
    if (worry_divisor == 1) {
        r %= modulo;
    }
    int next_monkey = (r % divisor == 0) ? true_monkey : false_monkey;
    return {next_monkey, r};
}

static int64_t solve_general(const day_11::ParsedData &parsed_data, int n_rounds, int worry_divisor) {
    std::vector<std::vector<int64_t> > current_items = parsed_data
        | ranges::views::keys
        | ranges::to<std::vector>();
    std::vector<int64_t> divisors = (
        parsed_data 
        | ranges::views::transform([](auto pm) {return (int64_t)std::get<1>(pm.second);})
        | ranges::to<std::vector>()
    );
    int64_t divisor_product = ranges::accumulate(
        divisors, 
        1LL, 
        [](int64_t lh, int64_t rh) {return lh * rh;}
    );
    std::vector<int64_t> inspections(parsed_data.size(), 0);
    for (auto round: ranges::views::ints(0, n_rounds)) {
        for (int i = 0; i < parsed_data.size(); ++i) {
            while(current_items[i].size()) {
                int64_t worry = current_items[i].back();
                current_items[i].pop_back();
                inspections[i] ++;
                auto [next_monkey, new_worry] = find_next_monkey_and_worry(parsed_data[i].second, worry, worry_divisor, divisor_product);
                current_items[next_monkey].push_back(new_worry);
            }
        }
    }
    std::sort(inspections.begin(), inspections.end());
    // std::cout << "bar" << (
    //     divisors 
    //     | ranges::views::transform([](auto x) {return std::to_string(x);}) 
    //     | ranges::views::join(" * ") 
    //     | ranges::to<std::string>()) << std::endl;
    // std::cout << "foo" << (
    //     inspections 
    //     | ranges::views::transform([](auto x) {return std::to_string(x);}) 
    //     | ranges::views::join(", ") 
    //     | ranges::to<std::string>()) << std::endl;
    return inspections.back() * *(inspections.rbegin() + 1);
}

day_11::ResultData day_11::solve_part_1(const ParsedData& parsed_data) {
    return solve_general(parsed_data, 20, 3);
}

day_11::ResultData day_11::solve_part_2(const ParsedData& parsed_data) {
    return solve_general(parsed_data, 10'000, 1);;
}

