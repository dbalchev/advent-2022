#include <iostream>
#include <advent_registry.h>


int Registry::run(int day, const char* input_filename) {
    auto solution_iterator = solutions.find(day);
    if (solution_iterator == solutions.end()) {
        std::cerr << "No solution for day " << day << std::endl;
        return 1;
    }
    return solution_iterator->second->run(input_filename);
}

Registry SOLUTION_REGISTRY;
