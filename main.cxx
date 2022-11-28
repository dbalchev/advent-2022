#include <iostream>
#include <unordered_map>

#include <gflags/gflags.h>

#include <day_00.h>
// Add include above this line

DEFINE_int32(day, -1, "Which day to run");
DEFINE_string(input, "", "Input file path");

int main(int argc, char** argv) {

    std::unordered_map<int, int(*)(const char*)> solutions = {
        {0, day_00_solution},
        // Add solution function above this line
    };

    gflags::ParseCommandLineFlags(&argc, &argv, true);

    auto solution_iter = solutions.find(FLAGS_day);
    if (solution_iter == solutions.end()) {
        std::cerr << "No solution for day " << FLAGS_day << std::endl;
        return 1;
    }

    return solution_iter->second(FLAGS_input.c_str());
}

