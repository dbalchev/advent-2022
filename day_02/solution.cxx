#include <iostream>
#include <fstream>
#include <filesystem>
#include <day_02.h>
#include <string>

namespace day_02 {
    std::vector<std::pair<int, int> > parse_input(const char* filename) {
        std::filesystem::path filepath = std::filesystem::absolute(filename);
        std::ifstream fin(filepath);
        if (!fin) {
            throw std::runtime_error("Cannot read from file " + filepath.string());
        }
        std::vector<std::pair<int, int> > result;

        while (fin) {
            std::string line;
            std::getline(fin, line);
            if (!line.length()) {
                break;
            }
            result.push_back(std::make_pair(line[0] - 'A', line[2] - 'X'));
        }
        return result;
    }

    static int score_play(int their, int mine) {
        int shape_score[] = {1, 2, 3};
        int outcome_score[] = {3, 6, 0};

        return shape_score[mine] + outcome_score[(3 + mine - their) % 3];
    }

    int score_part_1(const std::vector<std::pair<int, int> > &plan) {


        int total_score = 0;
        for (auto &round: plan) {
            total_score += score_play(round.first, round.second);
        }
        return total_score;
    }

    int score_part_2(const std::vector<std::pair<int, int> > &plan) {
        int shape_score[] = {1, 2, 3};
        int outcome_score[] = {3, 6, 0};

        int total_score = 0;
        for (auto &round: plan) {
            total_score += score_play(round.first, (5 + round.first + round.second) % 3);
        }
        return total_score;
    }
    
    int solution(const char* input_filename) {
        auto plan = parse_input(input_filename);
        std::cout << "Part 1: " << score_part_1(plan) << std::endl;
        std::cout << "Part 2: " << score_part_2(plan) << std::endl;

        return 0;
    }

}


