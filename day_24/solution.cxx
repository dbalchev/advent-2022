#include <iostream>
#include <queue>
#include <functional>
#include <unordered_set>
#include <unordered_map>

#include <day_24.h>
#include <TupleHash.h>

day_24::ParsedData day_24::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    std::vector<std::string> map;
    std::vector<std::tuple<int, int, int, int> > blizzards;

    std::string line;

    while(std::getline(fin, line) && !line.empty()) {
        for (int j = 0; j < line.size(); ++j) {
            int i = map.size();
            int di = 0, dj = 0;
            switch(line[j]) {
                case '<':
                    dj = -1;
                    break;
                case '>':
                    dj = 1;
                    break;
                case '^':
                    di = -1;
                    break;
                case 'v':
                    di = 1;
                    break;
            }
            if (di == 0 && dj == 0) {
                continue;
            }
            blizzards.push_back({i, j, di, dj});
            line[j] = '.';
        }
        map.push_back(line);
    }

    return {map, blizzards};
}

static std::vector<std::string> render_state(
    const std::vector<std::string>& map,
    const std::vector<std::tuple<int, int, int, int> > & blizzards
) {
    auto state = map;
    for (auto [i, j, di, dj]: blizzards) {
        state[i][j] = 'b';
    }
    return state;
}

static std::vector<std::tuple<int, int, int, int> > step_blizzards(
    std::vector<std::tuple<int, int, int, int> > blizzards,
    int height, int width
) {
    for (auto &[i, j, di, dj]: blizzards) {
        i += di;
        j += dj;
        if (i == 0) {
            i = height - 2;
        }
        if (i == height - 1) {
            i = 1;
        }
        if (j == 0) {
            j = width - 2;
        }
        if (j == width - 1) {
            j = 1;
        }
    }
    return blizzards;
}

static const std::vector<std::tuple<int, int> > MOVES = {
    {0, 0},
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
};

static int explore(const day_24::ParsedData &parsed_data, int n_trips) {
    auto &[map, initial_blizzards] = parsed_data;
    std::vector<
        std::tuple<
            std::vector<std::tuple<int, int, int, int> >,
            std::vector<std::string>
        >
    > per_turn_weather = {
        {initial_blizzards, render_state(map, initial_blizzards)}
    };

    int start_i = 0;
    int start_j = 0;
    for (;start_j < map[start_i].size() && map[start_i][start_j] != '.'; ++start_j) {

    }
    int end_i = map.size() - 1;
    int end_j = 0;

    for (;end_j < map[end_i].size() && map[end_i][end_j] != '.'; ++end_j) {

    }
    if (start_j == map[start_i].size() || end_j == map[end_i].size()) {
        throw std::runtime_error("didn't find start/end");
    }
    typedef std::tuple<int, int, int, int, int> StateType;
    std::priority_queue<
        StateType, 
        std::vector<StateType>,
        std::greater<StateType>
    > pq;
    std::unordered_set<std::tuple<int, int, int, int> > enqueued = {{0, 0, start_i, start_j}};
    // std::unordered_map<int, int> state_counter = {{abs(end_i - start_i) + abs(end_j - start_j), 1}};
    pq.push({n_trips *(abs(end_i - start_i) + abs(end_j - start_j)), 0, 0, start_i, start_j});

    while (!pq.empty()) {
        auto [answer_lower_bound, step_no, trip_idx, i, j] = pq.top();
        pq.pop();
        if (!enqueued.contains({step_no, trip_idx, i, j})) {
            throw std::runtime_error("hash set is behaving strangely after pop");
        }
        // state_counter[answer_lower_bound]--;
        
        if (
            (trip_idx % 2 == 0 && i == end_i && j == end_j) ||
            (trip_idx % 2 == 1 && i == start_i && j == start_j)
        ) {
            trip_idx ++;
            if (trip_idx == n_trips){
                return step_no;
            }
        }

        while (step_no + 1 >= per_turn_weather.size()) {
            // std::cout << step_no << " " << answer_lower_bound << " " << pq.size() << " " << enqueued.size() << std::endl; 
            // {
            //     for (auto [k, v]: state_counter) {
            //         std::cout << k << ": " << v << std::endl;
            //     }
            // }
            auto new_blizzards = step_blizzards(
                std::get<0>(per_turn_weather.back()), map.size(), map[0].size()
            );
            auto new_state = render_state(map, new_blizzards);
            per_turn_weather.push_back({
                new_blizzards, new_state
            });
        }
        const auto &[_1, current_state] = per_turn_weather[step_no];
        const auto &[_2, next_state] = per_turn_weather[step_no + 1];
        if (current_state[i][j] != '.') {
            continue;
        }
        for (auto &[di, dj]: MOVES) {
            auto ni = i + di;
            auto nj = j + dj;

            if (ni < 0 || ni >= next_state.size() || nj < 0 || nj >= next_state[ni].size() || next_state[ni][nj] != '.') {
                continue;
            }
            if (enqueued.contains({step_no + 1, trip_idx, ni, nj})) {
                continue;
            }
            auto target_i = trip_idx % 2 == 0 ? end_i : start_i;
            auto target_j = trip_idx % 2 == 0 ? end_j : start_j;
            auto new_lower_bound = 
                step_no + 1 
                + abs(target_i - ni) + abs(target_j - nj) 
                + (n_trips - trip_idx - 1) * (abs(end_i - start_i) + abs(end_j - start_j));
            // state_counter[new_lower_bound] ++;
            // std::cout << "step_no " << step_no << std::endl;
            pq.push({new_lower_bound, step_no + 1, trip_idx, ni, nj});
            enqueued.insert({step_no + 1, trip_idx, ni, nj});

            // std::cout << "step_no " << step_no << " " << enqueued.bucket_count() << std::endl;
            if (!enqueued.contains({step_no + 1, trip_idx, ni, nj})) {
                throw std::runtime_error("hash set is behaving strangely after insert");
            }
            if (pq.size() > 300'000'001) {
                std::cout << "pq is huge";
                throw std::runtime_error("pq is huge");
            }
        }
    }
    throw std::runtime_error("a* didn't yield a result?");
}

day_24::ResultData day_24::solve_part_1(const ParsedData& parsed_data) {
    return explore(parsed_data, 1);
}
day_24::ResultData day_24::solve_part_2(const ParsedData& parsed_data) {
    return explore(parsed_data, 3);
}

