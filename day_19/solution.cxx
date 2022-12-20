#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iterator>

#include <range/v3/view.hpp>
#include <range/v3/numeric.hpp>

#include <day_19.h>


using namespace day_19_ns;

static const std::unordered_map<std::string, int> RESOURCE_INDEX = {
    {"ore", 0},
    {"clay", 1},
    {"obsidian", 2},
    {"geode", 3},
};

static Resources parse_resources(const std::string &s) {
    Resources result{0, 0, 0, 0};

    auto segment_words = s
        | ranges::views::split(std::string(" and "))
        | ranges::views::transform([](auto segment) {
            return segment
                | ranges::views::split(std::string(" "))
                | ranges::views::transform([](auto word){
                    return ranges::to<std::string>(word);
                })
                | ranges::to<std::vector>();
        });

    for (auto words: segment_words) {
        if (words.size() != 2) {
            throw std::runtime_error("expected 2 words per segment but got " + std::to_string(words.size()));
        }
        int count = std::stoi(words[0]);
        auto index_it = RESOURCE_INDEX.find(words[1]);
        if (index_it == RESOURCE_INDEX.end()) {
            throw std::runtime_error("resource not found " + words[1]);
        }
        result[index_it->second] = count;
    }
    return result;
}
static Blueprint parse_blueprint(const std::string &s) {
    auto colon_pos = s.find(": ");
    if (colon_pos == std::string::npos) {
        throw std::runtime_error("no colon");
    }
    std::vector<Resources> costs(4);
    int blueprint_no = std::stoi(s.substr(10, colon_pos));
    auto after_colon = s.substr(colon_pos + 2);
    for (auto sentence_r: after_colon | ranges::views::split(std::string(". "))) {
        auto sentence = ranges::to<std::string>(sentence_r);

        if (sentence.back() == '.') {
            sentence.pop_back();
        }
        auto robot_index = sentence.find(" robot ");
        if (robot_index == std::string::npos) {
            throw std::runtime_error("cannot find robot");
        }
        auto resource = sentence.substr(5, robot_index - 5);
        auto index_it = RESOURCE_INDEX.find(resource);
        if (index_it == RESOURCE_INDEX.end()) {
            throw std::runtime_error("blueprint resource not found " + resource);
        }
        costs[index_it->second] = parse_resources(sentence.substr(
            robot_index + 13
        ));
    }
    return {
        blueprint_no,
        costs,
    };
}

day_19::ParsedData day_19::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    std::string line;
    ParsedData result;
    while(std::getline(fin, line)) {
        result.push_back(parse_blueprint(line));
    }
    return result;
}

template<>
struct std::hash<Resources> {
    std::size_t operator()(const Resources &p) const noexcept {
        std::size_t result = 0;
        for (auto x: p) {
            result = 91 * result + std::hash<d19_t>{}(x);
        }
        return result;
    }
};

template<typename T1, typename T2>
struct std::hash<std::tuple<T1, T2>> {
    std::size_t operator()(const std::tuple<T1, T2>& p) const noexcept {
        auto &[x, y] = p;
        return std::hash<T1>{}(x) + 31 * std::hash<T2>{}(y);
    }
};

template<typename T1, typename T2, typename T3>
struct std::hash<std::tuple<T1, T2, T3>> {
    std::size_t operator()(const std::tuple<T1, T2, T3>& p) const noexcept {
        auto &[x, y, z] = p;
        return std::hash<T1>{}(x) + 31 * (std::hash<T2>{}(y) + 31 * std::hash<T3>{}(z));
    }
};


struct BlueprintSolver {
    const std::vector<Resources> costs;
    const d19_t max_days;

    std::unordered_map<
        std::tuple<int, int, std::tuple<Resources, Resources> >,
        d19_t
    > memo;
    std::unordered_map<Resources, d19_t> best_possible_memo;
    std::unordered_map<
        std::tuple<Resources, Resources>,
        int
    > min_day;

    d19_t best_score;

    BlueprintSolver(int max_days, const std::vector<Resources>& costs)
        : max_days(max_days), costs(costs), best_score(0)
        {
        }
    d19_t best_possible_score(
            const d19_t days_left, 
            const d19_t obsidian_prod, 
            const d19_t obsidian_stash, 
            const d19_t geod_prod
        ) {
        if (days_left == 1) {
            return geod_prod;
        }
        if (days_left <= 0) { 
            return 0;
        }
        if (days_left > 2) {
            auto it = best_possible_memo.find({days_left, obsidian_prod, obsidian_stash, geod_prod});
            if (it != best_possible_memo.end()) {
                return it->second;
            }
        }
        d19_t best = best_possible_score(
            days_left - 1, 
            obsidian_prod + 1, 
            obsidian_stash + obsidian_prod, 
            geod_prod
        );
        if (obsidian_stash >= costs[3][2]) {
            best = std::max(
                best,
                best_possible_score(
                    days_left - 1, 
                    obsidian_prod, 
                    obsidian_stash + obsidian_prod - costs[3][2], 
                    geod_prod + 1
                )
            );
        }
        best += geod_prod;
        if (days_left > 2) {
            best_possible_memo.insert({{days_left, obsidian_prod, obsidian_stash, geod_prod}, best});
        }
        return best;
    }

    d19_t solve(int day, int next_construction, const Resources& r, const Resources &p) {
        if (day == max_days) {
            return r.back();
        }
        if (day > max_days) {
            throw std::runtime_error("too many days");
        }
        Resources new_r;
        {
            auto active_r = r;
            int days_needed = 0;
            for (int i = 0; i < 4; ++i) {
                auto c = costs[next_construction][i];
                if (c > 0 && p[i] == 0) {
                    days_needed = max_days + 1;
                } else if(p[i] >= 0) {
                    int x = (c - r[i] + p[i] - 1) / p[i];
                    x = std::max(x, 0);
                    days_needed = std::max(days_needed, x);
                }
            }
            if (day + days_needed >= max_days) { 
                int days_left = max_days - day;
                return r.back() + days_left * p.back();
            }
            day += days_needed;
            for (int i = 0; i < 4; ++i) {
                new_r[i] = r[i] + days_needed * p[i] - costs[next_construction][i];
                if (new_r[i] < 0) {
                    throw std::runtime_error("can't pay");
                }
                new_r[i] += p[i];
            }
        }
        auto new_p = p;
        new_p[next_construction] += 1;
        // {
        //     auto mdi = min_day.find({new_r, new_p});
        //     if (mdi == min_day.end()) {
        //         min_day.insert(mdi, {{new_r, new_p}, day});
        //     } else {
        //         if (mdi->second < day) {
        //             return 0;
        //         }
        //         mdi->second = day;
        //     }
        // }
        d19_t best_solution = 0;
        for (int new_next = 0; new_next < 4; ++new_next) {
            best_solution = std::max(
                best_solution,
                memo_solve(day + 1, new_next, new_r, new_p)
            );
        }
        return best_solution;
    }

    d19_t memo_solve(
        const int day, 
        const int next_construction, 
        const Resources& r, 
        const Resources &p
    ) {
        auto iter = memo.find({day, next_construction, {r, p}});
        if (iter != memo.end()) {
            return iter->second;
        }
        d19_t upper_bound = 
            r[3] + best_possible_score(
                max_days - day,
                p[2], r[2], p[3]
            );
        if (upper_bound <= best_score) { 
            return 0;
        }
        auto solution = solve(day, next_construction, r, p);
        best_score = std::max(best_score, solution);
        if (upper_bound < solution) {
            throw std::runtime_error("better than upper bound");
        }
        memo.insert(iter, {{day, next_construction, {r, p}}, solution});
        return solution;
    }
};

day_19::ResultData day_19::solve_part_1(const ParsedData& parsed_data) {
    d19_t result = 0;
    for (auto &[bp_index, costs]: parsed_data) {
        BlueprintSolver solver(24, costs);
        d19_t solution = 0;
        for (int first_factory = 0; first_factory < 4; ++first_factory) {
            solution = std::max(
                solver.solve(0, first_factory, {0, 0, 0, 0}, {1, 0, 0, 0}),
                solution
            );
        }

        result += bp_index * solution;
    }
    return result;
}

day_19::ResultData day_19::solve_part_2(const ParsedData& parsed_data) {
    d19_t result = 1;
    for (int i = 0; i < 3 && i < parsed_data.size(); ++i) {
        BlueprintSolver solver(32, std::get<1>(parsed_data[i]));
        d19_t solution = 0;
        for (int first_factory = 0; first_factory < 4; ++first_factory) {
            solution = std::max(
                solver.solve(0, first_factory, {0, 0, 0, 0}, {1, 0, 0, 0}),
                solution
            );
        }
        result *= solution;
    }
    return result;
}

