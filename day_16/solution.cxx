#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <chrono>

#include <range/v3/view.hpp>
#include <range/v3/numeric/accumulate.hpp>

#include <day_16.h>

day_16::ParsedData day_16::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    std::regex line_regex(
        "Valve ([A-Z]{2}) has flow rate=(\\d+); tunnels? leads? to valves? (.*)"
    );
    std::string line;
    std::smatch match_results;

    std::unordered_map<std::string, int> valve_names_remap = {
        {std::string("AA"), 0}
    };
    std::unordered_map<std::string, int> flow_rates;
    std::unordered_map<std::string, std::vector<std::string> > adj_valves;
    
    while (fin) {
        std::smatch match_results;

        line.clear();
        std::getline(fin, line);
        if (line.empty()) {
            break;
        }
        if (!std::regex_match(line, match_results, line_regex)) {
            throw std::runtime_error("Line doesn't match '" + line);
        }
        std::string valve_name = match_results[1].str();
        auto rename_it = valve_names_remap.find(valve_name);
        if (rename_it == valve_names_remap.end()) {
            valve_names_remap.insert({valve_name, valve_names_remap.size()});
        }
        flow_rates.insert({valve_name, std::stoi(match_results[2].str())});
        std::string unsplit_adj = match_results[3].str();
        adj_valves.insert({
                valve_name, 
                unsplit_adj
                | ranges::views::split(std::string(", "))
                | ranges::views::transform([](auto s) -> std::string {
                    return ranges::to<std::string>(s);
                })
                | ranges::to<std::vector>()
            }
        );
    }
    ParsedData result(valve_names_remap.size(), {0, {}});
    for (auto &[valve_name, valve_id]: valve_names_remap) {
        result[valve_id] = {
            flow_rates[valve_name],
            adj_valves[valve_name]
            | ranges::views::transform([&](auto &s) -> int {
                auto it = valve_names_remap.find(s);
                if (it == valve_names_remap.end()) {
                    throw std::runtime_error("Cannot remap " + s);
                }
                return it->second;
            })
            | ranges::to<std::vector>()
        };
    }
    return result;
}

typedef std::tuple<
    int, // current pressure NOT released
    int, // timestep
    int, // pressure NOT released per timestep
    int, // my current node,
    int, // helper's current node,
    std::vector<bool> // opened_map
> State;

template<>
struct std::hash<std::tuple<int, int, std::vector<bool> >> {
    std::size_t operator()(const std::tuple<int, int, std::vector<bool> >& p) const noexcept {
        auto [x, y, z] = p;
        return std::hash<int>{}(x) * 17 * 17 + std::hash<int>{}(y) * 17 + std::hash<std::vector<bool>>{}(z);
    }
};


static int release_the_pressure(const day_16::ParsedData& parsed_data, int max_steps, bool have_help) {
    int total_capacity = ranges::accumulate(
        parsed_data
        | ranges::views::transform([](auto &v) -> int{
            return std::get<0>(v);
        }),
        0,
        [](int lh, int rh) {return lh + rh;}
    );
    auto last_print = std::chrono::system_clock::now();
    std::priority_queue<State, std::vector<State>, std::greater<State> > pq;
    std::unordered_set<std::tuple<int, int, std::vector<bool> > > visited;
    pq.push({0, 0, total_capacity, 0, 0, std::vector<bool>(parsed_data.size(), false)});
    int min_urppt = total_capacity;
    int max_acceptable_urp = total_capacity * max_steps;
    while(!pq.empty()) {
        auto [current_urp, t, urppt, my_node, helper_node, opened] = pq.top();
        if (t == max_steps || urppt == 0) {
            return total_capacity * max_steps - current_urp;
        }
        min_urppt = std::min(min_urppt, urppt);
        pq.pop();
        auto &[my_valve_size, my_adj_valves] = parsed_data[my_node];
        auto &[helper_valve_size, helper_adj_values] = parsed_data[helper_node];
        auto now = std::chrono::system_clock::now();

        if (
            visited.contains({my_node, helper_node, opened}) 
            || visited.contains({helper_node, my_node, opened}) 
            || current_urp > max_acceptable_urp
        ) {
            continue;
        }
        max_acceptable_urp = std::min(
            max_acceptable_urp,
            current_urp + (max_steps - t) * urppt
        );
        visited.insert({my_node, helper_node, opened});
        std::chrono::duration<double> diff = now - last_print;
        if (false) {
            last_print = now;
            int o = 0;
            for (auto x: opened) { o+=x;}
            std::cout << 
                "URP " << current_urp << 
                " timestep " << t << 
                " min_urppt " << min_urppt << 
                " max_acceptable_urp " << max_acceptable_urp << 
                " Node " << my_node << " " << helper_node <<
                " opened " << o << 
                " URPPT " << urppt << " / " << total_capacity << std::endl;
                
        }
        auto next_urp = current_urp + urppt;
        if (next_urp > max_acceptable_urp) {
            continue;
        }
        if (!have_help) {
            for (auto v: my_adj_valves) {
                if (visited.contains({v, helper_node, opened})) {
                    continue;
                }
                pq.push({
                    next_urp,
                    t + 1,
                    urppt,
                    v,
                    helper_node,
                    opened,
                });
            }
            if (!opened[my_node] && my_valve_size > 0) {
                opened[my_node] = true;
                urppt -= my_valve_size;
                max_acceptable_urp = std::min(
                    max_acceptable_urp,
                    next_urp + (max_steps - t - 1) * urppt
                );
                pq.push({
                    next_urp,
                    t + 1,
                    urppt,
                    my_node,
                    helper_node,
                    std::move(opened)
                });
            }
        } else {
            auto my_next = my_adj_valves;
            my_next.push_back(my_node);
            auto helper_next = helper_adj_values;
            helper_next.push_back(helper_node);
            for (auto my_v: my_next) {
                for (auto helper_v: helper_next) {
                    auto new_urppt = urppt;
                    auto new_opend = opened;
                    if (my_v == my_node) {
                        if (!new_opend[my_node] && my_valve_size > 0) {
                            new_opend[my_node] = true;
                            new_urppt -= my_valve_size;
                        } else {
                            continue;
                        }
                    }
                    if (helper_v == helper_node) {
                        if (!new_opend[helper_node] && helper_valve_size > 0) {
                            new_opend[helper_node] = true;
                            new_urppt -= helper_valve_size;
                        } else {
                            continue;
                        }
                    }
                    max_acceptable_urp = std::min(
                        max_acceptable_urp,
                        next_urp + (max_steps - t - 1) * new_urppt
                    );
                    if (visited.contains({my_v, helper_v, new_opend}) || visited.contains({helper_v, my_v, new_opend})) {
                        continue;
                    }
                    pq.push({
                        next_urp,
                        t + 1,
                        new_urppt,
                        my_v,
                        helper_v,
                        std::move(new_opend)
                    });
                }
            }
        }
    }

    throw std::runtime_error("Ran out of queue?");
}

day_16::ResultData day_16::solve_part_1(const ParsedData& parsed_data) {
    return release_the_pressure(parsed_data, 30, false);
}
day_16::ResultData day_16::solve_part_2(const ParsedData& parsed_data) {
    return release_the_pressure(parsed_data, 26, true);
}

