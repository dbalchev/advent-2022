#include <iostream>

#include <gflags/gflags.h>

#include <advent_registry.h>

DEFINE_int32(day, -1, "Which day to run");
DEFINE_string(input, "", "Input file path");

int main(int argc, char** argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    return SOLUTION_REGISTRY.run(FLAGS_day, FLAGS_input.c_str());
}