#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iterator>

#include<range/v3/view.hpp>

#include <day_19.h>


using namespace day_19_ns;

static const std::unordered_map<std::string, int> RESOURCE_INDEX = {
    {"ore", 0},
    {"clay", 1},
    {"obsidian", 2},
    {"geode", 3},
};

static Resources parse_resources(const std::string &s) {
    Resources result(4, 0);

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

static Resources produce(const Resources &r, const Resources &p) {
    return ranges::views::zip(r, p)
        | ranges::views::transform([](auto rp) -> d19_t {
            auto [rx, px] = rp;
            return rx + px;
        })
        | ranges::to<std::vector>();
}

static bool dominates(const Resources &lh, const Resources &rh) {
    bool strict = false;
    for (auto [l, r]: ranges::views::zip(lh, rh)) {
        if (l > r) {
            strict = true;
        } else if (l < r) {
            return false;
        }
    }
    return strict;
}

struct BlueprintSolver {
    std::vector<Resources> costs;
    std::unordered_map<
        std::tuple<int, int, std::tuple<Resources, Resources> >,
        d19_t
    > memo;

    std::vector<Resources> dominators;
    Resources max_resources;
    Resources max_production;
    int max_days;

    BlueprintSolver(int max_days, const std::vector<Resources>& costs)
        : costs(costs), max_days(max_days),
            dominators(4, Resources(9, 0)),
            max_resources(4, 45),
            max_production(4, 0)
        {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 3; ++j) {
                    max_resources[j] = 45; //std::max(max_resources[j], 2 * costs[i][j]);
                    max_production[j] = std::max(max_production[j], costs[i][j]);
                }
            }
            max_resources[0] = 10;
            max_resources[3] = max_production[3] = std::numeric_limits<d19_t>::max();
        }

    d19_t solve(int day, int next_construction, const Resources& r, const Resources &p) {
        if (day == max_days) {
            return r.back();
        }
        for (int i = 0; i < 4; ++i) {
            if (r[i] > max_resources[i] || p[i] > max_production[i]) {
                return 0;
            }
        }
        {
            auto new_r = ranges::views::zip(r, costs[next_construction])
                | ranges::views::transform([](auto rc) -> d19_t {
                    auto [rx, cx] = rc;
                    return rx - cx;
                })
                | ranges::to<std::vector>();
            bool can_pay = std::all_of(new_r.begin(), new_r.end(), [](auto x){
                return x >= 0;
            });
            if (can_pay) {
                new_r = produce(new_r, p);
                auto new_p = p;
                new_p[next_construction] += 1;
                d19_t best_solution = 0;
                for (int new_next = 0; new_next < 4; ++new_next) {
                    best_solution = std::max(
                        best_solution,
                        memo_solve(day + 1, new_next, new_r, new_p)
                    );
                }
                return best_solution;
            }
        }
        auto new_r = produce(r, p);
        return memo_solve(day + 1, next_construction, new_r, p);
    }

    d19_t memo_solve(int day, int next_construction, const Resources& r, const Resources &p) {
        auto iter = memo.find({day, next_construction, {r, p}});
        if (iter != memo.end()) {
            return iter->second;
        }
        {
            Resources dominaton_vector = {day};
            auto inserter = std::back_insert_iterator(dominaton_vector);
            std::copy(r.begin(), r.end(), inserter);
            std::copy(p.begin(), p.end(), inserter);
            if (dominates(dominators[next_construction], dominaton_vector)) {
                return -1;
            }
            for (int di; di < 9; ++di) {
                dominators[next_construction][di] = std::max(
                    dominators[next_construction][di], dominaton_vector[di]
                );
            }
        }
        auto solution = solve(day, next_construction, r, p);
        memo.insert(iter, {{day, next_construction, {r, p}}, solution});
        return solution;
    }
};

day_19::ResultData day_19::solve_part_1(const ParsedData& parsed_data) {
    d19_t result = 0;
    for (auto &[bp_index, costs]: parsed_data) {
        BlueprintSolver solver = {24, costs};
        d19_t solution = 0;
        for (int first_factory = 0; first_factory < 4; ++first_factory) {
            solution = std::max(
                solver.solve(0, first_factory, {0, 0, 0, 0}, {1, 0, 0, 0}),
                solution
            );
        }
        std::cout << solution << std::endl;
        result += bp_index * solution;
    }
    return result;
}

typedef std::tuple<
    Resources, // cost
    Resources, // resource production
    Resources  // factory production
> MegaAction;

static std::vector<MegaAction> 
combine_mega_actions(
    const std::vector<MegaAction> &lh, int lh_minutes,
    const std::vector<MegaAction> &rh, int rh_minutes,
    bool allow_positive_cost,
    const Resources &max_resources,
    const Resources &max_factories
) {
    std::vector<MegaAction> current_actions;
    for (const auto& [cost_1, resources_1, factories_1]: lh) {
        {
            auto me = std::max_element(cost_1.begin(), cost_1.end());
            if (!allow_positive_cost && *me > 0){
                continue;
            }
        }
        for (const auto& [cost_2, resources_2, factories_2]: rh) {
            Resources cost, resources, factories;
            bool within_limits = true;
            for (int i = 0; i < 4; ++i) {
                d19_t mid_r = (
                    resources_1[i]
                    - cost_2[i]
                );

                cost.push_back(cost_1[i] + (mid_r < 0 ? -mid_r: 0));
                resources.push_back(
                    resources_2[i]
                    + factories_1[i] * rh_minutes
                    + (mid_r > 0 ? mid_r: 0)
                );
                factories.push_back(factories_1[i] + factories_2[i]);
                // within_limits = 
                //     within_limits 
                //     && resources[i] <= max_resources[i]
                //     && cost[i] <= max_resources[i]
                //     && factories[i] <= max_factories[i];
            }
            auto me = std::max_element(cost.begin(), cost.end());
            if (within_limits && (allow_positive_cost || *me == 0)) {
                current_actions.push_back({cost, resources, factories});
                MegaAction a_10_12 = {
                    {4, 14, 0, 0},
                    {1, 0, 1, 0},
                    {0, 1, 1, 0},  
                };
                MegaAction a_8_12 = {
                    {2, 14, 0, 0},
                    {1, 0, 1, 0},
                    {0, 1, 1, 0},
                };
                if (current_actions.back() == a_10_12) {
                    std::cout << "A 10 12 generated in " << 2 * rh_minutes << std::endl;
                }
                if (current_actions.back() == a_8_12) {
                    std::cout << "A 8 12 generated in " << 2 * rh_minutes << std::endl;
                }
            }
        }
    }
    std::sort(current_actions.begin(), current_actions.end());
    auto last_unique = std::unique(current_actions.begin(), current_actions.end());
    current_actions.resize(last_unique - current_actions.begin());
    std::vector<MegaAction> filtered;
    std::unordered_map<std::tuple<Resources, Resources>, std::vector<Resources> > grouped;
    for (auto &[c, r, p]: current_actions) {
        grouped[{c, p}].push_back(r);
    }
    for (auto &[cp, rs]: grouped) {
        auto &[c, p] = cp;
        for (auto &r1: rs) {
            bool dominated = false;
            bool is_a_8_12 = c == Resources{2, 14, 0, 0} 
                && r1 == Resources{1, 0, 1, 0} 
                && p == Resources{0, 1, 1, 0};
            for (auto &r2: rs) {
                if (r1 == r2) {
                    continue;
                }
                bool r2_dominates = true;
                for (int i = 0; i < 4; ++i) {
                    if (r1[i] > r2[i]) {
                        r2_dominates = false;
                        break;
                    }
                }
                if (r2_dominates) {
                    if (is_a_8_12) {
                        std::cout << "dominator" << std::endl;
                        for (int i = 0; i < 4; ++i) {
                            std::cout << r2[i] << " ";
                        }
                        std::cout << std::endl;
                    }
                    dominated = true;
                    break;
                }
            }   
            if (is_a_8_12) 
                {
                std::cout << "a_8_12 dominated = " << dominated << " in " << 2 * rh_minutes << std::endl;
            }
            if (!dominated) {
                filtered.push_back({c, r1, p});
            }
        }
    }
    return filtered;
     
}

struct ImprovedBlueprintSolver
{
    std::vector<
        std::vector<MegaAction>
    > actions;

    Resources max_resources;
    Resources max_factories;

    ImprovedBlueprintSolver(int iterations, const std::vector<Resources> &costs)
    :
        max_resources(4, 0),
        max_factories(4, 0)
    {
        std::vector<MegaAction> simple_actions;
        simple_actions.push_back(
            {{0, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}}
        );
        
        for (int i = 0; i < 4; ++i) {
            Resources factories_produced(4, 0);
            factories_produced[i] = 1;
            simple_actions.push_back({costs[i], {1, 0, 0, 0}, factories_produced});
            for (int j = 0; j < 3; ++j) {
                max_resources[j] = 45; //std::max(max_resources[j], 2 * costs[i][j]);
                max_factories[j] = std::max(max_factories[j], costs[i][j]);
            }
        }
        max_resources[0] = 10;
        max_resources[3] = max_factories[3] = std::numeric_limits<d19_t>::max();
        actions.push_back(simple_actions);
        for (int iter = 0; iter < iterations; ++iter) {
            int num_minutes = 1 << iter;
            
            actions.push_back(combine_mega_actions(
                actions.back(), num_minutes, actions.back(), num_minutes, true,
                max_resources, max_factories
            ));
        }
    }

    d19_t solve_24() {
        auto ca = actions[2];
        MegaAction a_8_12 = {
            {2, 14, 0, 0},
            {1, 0, 1, 0},
            {0, 1, 1, 0},
        };
        for (auto &x: ca) {
            if (x == a_8_12) {
                std::cout << "Expected action found in ca" << std::endl;
            }
        }
        for (int i = 1; i < 5; ++i) {
            ca = combine_mega_actions(ca, 4 * i, actions[2], 4, false, max_resources, max_factories);
            std::cout << "size_" << i << " " << ca.size() << std::endl;
            for (auto &x: ca) {
                MegaAction m08 = {{0, 0, 0, 0}, {2, 9, 0, 0}, {0, 3, 0, 0}};
                MegaAction m12 = {{0, 0, 0, 0}, {1, 7, 1, 0}, {0, 4, 1, 0}};
                MegaAction m16 = {{0, 0, 0, 0}, {2, 9, 6, 0}, {0, 4, 2, 0}};
                if (x == m08) {
                    std::cout << "Expected for m08 found" << std::endl;
                }
                if (x == m12) {
                    std::cout << "Expected for m12 found" << std::endl;
                }
                if (x == m16) {
                    std::cout << "Expected for m16 found" << std::endl;
                }
            }
        }
        // auto ca = combine_mega_actions(
        //     actions[3], 8, actions[3], 8, false, max_resources, max_factories
        // );
        // std::cout << "size_1 " << ca.size() << std::endl;
        // ca = combine_mega_actions(
        //     std::move(ca), 8, actions[3], 8, false, max_resources, max_factories
        // );
        // std::cout << "size_2 " << ca.size() << std::endl;
        d19_t max = 0;
        int c3 = 0;
        bool printed = false;
        for (auto &[c, r, p]: ca) {
            if (r.back() == 3) {
                c3 += 1;
                if (!printed && p[1] == 4 && p[0] == 0) {
                    std::cout << "====" << std::endl;
                    for (int j = 0; j < 4; ++j) {
                        std::cout << c[j] << " " << r[j] << " " << p[j] << std::endl;
                    }
                    std::cout << "====" << std::endl;
                    printed = true;
                }
            }
            max = std::max(r.back(), max);

                        // if (i < 2) {
            // std::cout << "====" << std::endl;
            // for (int j = 0; j < 4; ++j) {
            //     std::cout << c[j] << " " << r[j] << " " << p[j] << std::endl;
            // }
            // std::cout << "====" << std::endl;
            // }
        }
        std::cout << "c3 " << c3 << std::endl;
        return max;
    }

};
day_19::ResultData day_19::solve_part_2(const ParsedData& parsed_data) {
    return -1;
    ImprovedBlueprintSolver solver(3, std::get<1>(parsed_data[0]));
    int i = 0;
    for (auto &actions: solver.actions) {
        Resources max_resources(4, 0);
        int zero_cost_actions = 0;
        for (auto &[cost, resources, production]: actions) {
            auto me = std::max_element(cost.begin(), cost.end());
            for (int i = 0; i < 4; ++i) {
                max_resources[i] = std::max(max_resources[i], resources[i]);
            }
            // if (i < 2 || (i == 2 && *me == 0)) {
            //     std::cout << "====" << std::endl;
            //     for (int j = 0; j < 4; ++j) {
            //         std::cout << cost[j] << " " << resources[j] << " " << production[j] << std::endl;
            //     }
            //     std::cout << "====" << std::endl;
            // }
            zero_cost_actions += *me == 0;
        }
        std::cout << (1 << i++) << " " << actions.size() << " " << zero_cost_actions << std::endl;
        for (int i = 0; i < 4; ++i) {
            std::cout << max_resources[i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << solver.solve_24() << std::endl;
    return 30;
}

