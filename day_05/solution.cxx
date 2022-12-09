#include <iostream>

#include <day_05.h>
#include <algorithm>
#include <iterator>
#include <stdio.h>

using namespace day05_ns;

day_05::ParsedData day_05::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);

    ContainerState container_state;

    while (fin) {
        std::string line;
        std::getline(fin, line);
        if (!line.length()) {
            break;
        }
        auto inferred_num_stacks = (line.length() + 1) / 4;
        if (inferred_num_stacks > container_state.size()) {
            container_state.resize(inferred_num_stacks);
        }
        for (int chunk_start = 0; chunk_start + 3 <= line.length(); chunk_start += 4) {
            Crate crate = line[chunk_start + 1];
            if (isalpha(crate)) {
                container_state[chunk_start / 4].push_back(crate);
            }
        }
    }
    for (auto& stack: container_state) {
        std::reverse(stack.begin(), stack.end());
    }

    std::vector<Move> moves;

    while(fin) {
        std::string line;
        std::getline(fin, line);

        if (!line.length()) {
            break;
        }

        int count, from, to;

        sscanf(line.c_str(), "move %d from %d to %d", &count, &from, &to);
        moves.push_back({count, from, to});
    }

    return {container_state, moves};
}

static std::string compute_output(const ContainerState& container_state) {
    std::string result;
    for (auto& stack: container_state){
        result.push_back(stack.back());
    }

    return result;
}

day_05::ResultData day_05::solve_part_1(const ParsedData& parsed_data) {
    auto container_snapshot = parsed_data.first;

    for (auto [count, from, to]: parsed_data.second) {
        from--;
        to--;
        for (int i = 0; i < count; ++i) {
            Crate crate = container_snapshot[from].back();
            container_snapshot[from].pop_back();
            container_snapshot[to].push_back(crate);
        }
    }
    return compute_output(container_snapshot);

}
day_05::ResultData day_05::solve_part_2(const ParsedData& parsed_data) {
    auto container_snapshot = parsed_data.first;

    for (auto [count, from, to]: parsed_data.second) {
        from--;
        to--;
        std::vector<Crate> in_flight;
        for (int i = 0; i < count; ++i) {
            Crate crate = container_snapshot[from].back();
            container_snapshot[from].pop_back();
            in_flight.push_back(crate);
        }
        std::copy(
            in_flight.rbegin(), in_flight.rend(), std::back_insert_iterator(container_snapshot[to])
        );
    }
    return compute_output(container_snapshot);
}

