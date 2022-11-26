#include <iostream>

#include <gflags/gflags.h>

DEFINE_int32(day, 0, "Which day to run");

int main(int argc, char** argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    std::cout << "hey advent " << FLAGS_day << std::endl;
    return 0;
}