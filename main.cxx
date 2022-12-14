#include <iostream>
#include <unordered_map>

#include <gflags/gflags.h>

#include <day_00.h>
#include <day_01.h>
#include <day_02.h>
#include <day_03.h>
#include <day_04.h>
#include <day_05.h>
#include <day_06.h>
#include <day_07.h>
#include <day_08.h>
#include <day_09.h>
#include <day_10.h>
#include <day_11.h>
#include <day_12.h>
#include <day_13.h>
#include <day_14.h>
#include <day_15.h>
#include <day_16.h>
#include <day_17.h>
#include <day_18.h>
#include <day_19.h>
#include <day_20.h>
#include <day_21.h>
#include <day_22.h>
#include <day_23.h>
#include <day_24.h>
#include <day_25.h>
// Add include above this line

DEFINE_int32(day, -1, "Which day to run");
DEFINE_string(input, "", "Input file path");

int main(int argc, char** argv) {

    std::unordered_map<int, int(*)(const char*)> solutions = {
        {0, day_00::solution},
        {1, day_01::solution},
        {2, day_02::solution},
        {3, day_03::solution},
        {4, day_04::solution},
        {5, day_05::solution},
        {6, day_06::solution},
        {7, day_07::solution},
        {8, day_08::solution},
        {9, day_09::solution},
        {10, day_10::solution},
        {11, day_11::solution},
        {12, day_12::solution},
        {13, day_13::solution},
        {14, day_14::solution},
        {15, day_15::solution},
        {16, day_16::solution},
        {17, day_17::solution},
        {18, day_18::solution},
        {19, day_19::solution},
        {20, day_20::solution},
        {21, day_21::solution},
        {22, day_22::solution},
        {23, day_23::solution},
        {24, day_24::solution},
        {25, day_25::solution},
        // Add solution function above this line
    };

    gflags::ParseCommandLineFlags(&argc, &argv, true);

    auto solution_iter = solutions.find(FLAGS_day);
    if (solution_iter == solutions.end()) {
        std::cerr << "No solution for day " << FLAGS_day << std::endl;
        return 1;
    }

    try {
        return solution_iter->second(FLAGS_input.c_str());
    } catch (std::exception ex) {
        std::cerr << "Exception " << ex.what() << std::endl;
    }
    
}




