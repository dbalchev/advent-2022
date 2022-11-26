#pragma once
#include <unordered_map>
#include <memory>


class Solution {
public:
    virtual int run(const char* input_filename) = 0;
    virtual ~Solution() {};
};

class Registry {
public:
    template<typename SolutionType>
    void register_solution(int day) {
        auto result = solutions.emplace(
            std::make_pair(day, std::unique_ptr<SolutionType>(new SolutionType))
        );
    }
    int run(int day, const char* input_filename);
private:
    std::unordered_map<int, std::unique_ptr<Solution> > solutions;
};


template<typename SolutionType>
class RegisterSolution {
public:
    RegisterSolution(Registry &registry, int day) {
        registry.register_solution<SolutionType>(day);
    }
};
