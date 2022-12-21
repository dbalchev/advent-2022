#include <iostream>
#include <algorithm>
#include <unordered_set>

#include <range/v3/view.hpp>

#include <day_21.h>

using namespace day_21_ns;

day_21::ParsedData day_21::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    ParsedData result;
    std::string name, first;
    while(fin >> name >> first) {
        if (name.back() == ':') {
            name.pop_back();
        }
        if (std::all_of(first.begin(), first.end(), isnumber)) {
            result.insert({
                name,
                std::stoll(first)
            });
        } else {
            std::string second;
            char op;
            fin >> op >> second;
            result.insert({
                name,
                OpMonkey {first, op, second}
            });
        }
    }

    return result;
}

static int64_t evaluate(const day_21::ParsedData& parsed_data, const std::string &root_name) {
    std::unordered_map<std::string, int64_t> monkey_cache;
    std::vector<std::string> topo_sort = {root_name};
    std::unordered_set<std::string> pushed = {root_name};
    for (int i = 0; i < topo_sort.size(); ++i) {
        const auto monkey_it = parsed_data.find(topo_sort[i]);
        if (monkey_it == parsed_data.end()) {
            throw std::runtime_error("unknown monkey");
        }
        if (monkey_it->second.index() == 0) {
            continue;
        } 
        const auto& [m1, _, m2] = std::get<1>(monkey_it->second);
        if (!pushed.contains(m1)) {
            pushed.insert(m1);
            topo_sort.push_back(m1);
        }
        if (!pushed.contains(m2)) {
            pushed.insert(m2);
            topo_sort.push_back(m2);
        }
    }
    for (const auto &monkey_name: ranges::views::reverse(topo_sort)) {
        const auto monkey_it = parsed_data.find(monkey_name);
        if (monkey_it == parsed_data.end()) {
            throw std::runtime_error("unknown topo monkey");
        }
        if (monkey_it->second.index() == 0) {
            monkey_cache.insert({monkey_name, std::get<0>(monkey_it->second)});
            continue;
        }
        const auto& [m1, op, m2] = std::get<1>(monkey_it->second);
        const auto m1_it = monkey_cache.find(m1);
        if (m1_it == monkey_cache.end()) {
            throw std::runtime_error("m1 not in cache");
        }
        const auto m2_it = monkey_cache.find(m2);
        if (m2_it == monkey_cache.end()) {
            throw std::runtime_error("m2 not in cache");
        }
        int64_t result, m1_v = m1_it->second, m2_v = m2_it->second;
        switch(op) {
            case '+':
                result = m1_v + m2_v;
                break;
            case '-':
                result = m1_v - m2_v;
                break;
            case '*':
                result = m1_v * m2_v;
                break;
            case '/':
                result = m1_v / m2_v;
                break;
            
        }
        // std::cout << monkey_name << " = " << result << std::endl;
        monkey_cache.insert({monkey_name, result});
    }
    const auto root_result = monkey_cache.find(root_name);
    if (root_result == monkey_cache.end()) {
        throw std::runtime_error("root not in cache");
    }
    return root_result->second;
}

day_21::ResultData day_21::solve_part_1(const ParsedData& parsed_data) {
    return evaluate(parsed_data, "root");
}
day_21::ResultData day_21::solve_part_2(const ParsedData& parsed_data) {
    std::unordered_map<std::string, std::vector<std::string> > dependents;
    for (const auto& [monkey_name, monkey_value]: parsed_data) {
        if (monkey_value.index() == 0) {
            continue;
        }
        const auto& [m1, _, m2] = std::get<1>(monkey_value);
        dependents[m1].push_back(monkey_name);
        dependents[m2].push_back(monkey_name);
    }

    auto rewritten_data = parsed_data;
    std::string x = "humn";
    while (x != "root") {
        const auto x_it = dependents.find(x);
        if (x_it == dependents.end()) {
            throw std::runtime_error("Couldn't find x");
        }
        if (x_it->second.size() != 1) {
            throw std::runtime_error("dependents[x] == " + std::to_string(x_it->second.size()));
        }
        auto dep = x_it->second[0];
        const auto dep_it = parsed_data.find(dep);
        if (dep_it == parsed_data.end()) {
            throw std::runtime_error("Couldn't find dep");
        }
        if (dep_it->second.index() == 0) {
            throw std::runtime_error("dep should be op");
        }
        const auto& [m1, op, m2] = std::get<1>(dep_it->second);
        if (dep == "root") {
            const auto other = (m1 == x) ? m2 : m1;
            rewritten_data.erase("root");
            auto other_it = parsed_data.find(other);
            if (other_it == parsed_data.end()) {
                throw std::runtime_error("Couldn't find other");
            }
            // std::cout << "other = " << other << std::endl; 
            rewritten_data[x] = other_it->second;
            rewritten_data.erase(other);
            break;
        }
        OpMonkey new_op = {"", '_', ""};
        if (m1 == x) {
            switch (op) {
                // dep = x _ m2
                case '+':
                    new_op = {dep, '-', m2};
                    break;
                case '-':
                    new_op = {dep, '+', m2};
                    break;
                case '*':
                    new_op = {dep, '/', m2};
                    break;
                case '/':
                    new_op = {dep, '*', m2};
                    break;
            }
        } else {
            if (m2 != x) {
                throw std::runtime_error("m2 != x");
            }
            switch (op) {
                // dep = m1 _ x
                case '+':
                    new_op = {dep, '-', m1};
                    break;
                case '-':
                    new_op = {m1, '-', dep};
                    break;
                case '*':
                    new_op = {dep, '/', m1};
                    break;
                case '/':
                    new_op = {m1, '/', dep};
                    break;
            }
        }
        if (std::get<1>(new_op) == '_') {
            throw std::runtime_error("not rewritten");
        }
        rewritten_data[x] = new_op;
        // std::cout << x << ": " << std::get<0>(new_op) << std::get<1>(new_op) << std::get<2>(new_op) << std::endl;
        x = dep;
    }

    return evaluate(rewritten_data, "humn");
}

