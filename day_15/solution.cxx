#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

#include <day_15.h>

using namespace day_15_ns;

day_15::ParsedData day_15::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    int64_t desired_y, max_coordinates;
    fin >> desired_y >> max_coordinates;
    std::vector<std::tuple<day_15_ns::Location, day_15_ns::Location>> sensors;
    std::string line;
    std::getline(fin, line);

    while (fin) {
        std::getline(fin, line);
        if (line.empty()) {
            break;
        }
        int64_t sx, sy, bx, by;
        sscanf(
            line.c_str(),
            "Sensor at x=%lld, y=%lld: closest beacon is at x=%lld, y=%lld",
            &sx, &sy, &bx, &by
        );
        sensors.push_back({{sx, sy}, {bx, by}});
    }
    return {{desired_y, max_coordinates}, sensors};
}
static const int64_t END = -1;
static const int64_t BEGIN = 1;

static std::tuple<int64_t, int64_t> compute_n_covered_spaces(
    const SensorData& sensors, int64_t desired_y, int64_t min_x, int64_t max_x 
) {

    std::vector<std::tuple<int64_t, int64_t> > events;
    for (auto &[sensor, beacon]: sensors) {
        auto [sx, sy] = sensor;
        auto [bx, by] = beacon;

        int64_t l1_distance = abs(sx - bx) + abs(sy - by);
        int64_t y_distance = abs(sy - desired_y);
        int64_t x_distance = l1_distance - y_distance;
        if (x_distance < 0) {
            continue;
        }

        events.push_back({sx - x_distance, BEGIN});
        events.push_back({sx + x_distance, END});
    }
    std::sort(events.begin(), events.end());

    int64_t n_covering_sensors = 0;
    int64_t covered_xs = 0;
    int64_t current_x = std::get<0>(events[0]);
    int64_t first_uncovered_x = min_x - 1;

    for (auto [event_x, event_type]: events) {
        if (n_covering_sensors > 0) {
            int64_t effective_start = std::max(current_x, min_x);
            int64_t effective_end = std::min(event_x, max_x);
            covered_xs += std::max(effective_end - effective_start, 0LL);
        } else if (
            first_uncovered_x == min_x - 1 && event_x > current_x + 1 && current_x > -1
        ) {
            first_uncovered_x = current_x + 1;
        }
        current_x = event_x;
        n_covering_sensors += event_type;
    }
    return {covered_xs, first_uncovered_x};

}

day_15::ResultData day_15::solve_part_1(const ParsedData& parsed_data) {
    auto &[task_spec, sensors] = parsed_data;
    auto [desired_y, _1] = task_spec;

    auto [covered_xs, _2] = compute_n_covered_spaces(
        sensors, 
        desired_y, 
        std::numeric_limits<int64_t>::min() + 1, 
        std::numeric_limits<int64_t>::max()
    );
    return covered_xs;
}
day_15::ResultData day_15::solve_part_2(const ParsedData& parsed_data) {
    auto &[task_spec, sensors] = parsed_data;
    auto [_, max_coordinates] = task_spec;

    int64_t bx = -1;
    int64_t by = -1;
    for (int64_t y = 0; y <= max_coordinates; y++) {
        auto [covered_spaces, first_uncovered_x] = compute_n_covered_spaces(
            sensors, y, 0, max_coordinates
        );
        if (covered_spaces < max_coordinates) {
            bx = first_uncovered_x;
            by = y;
            break;
        }
    }
    if (by == -1) {
        throw std::runtime_error("Coudln't find a beacon position");
    }

    return bx * 4'000'000 + by;
}

