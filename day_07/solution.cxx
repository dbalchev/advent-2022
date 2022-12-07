#include <iostream>

#include <day_07.h>
#include <string>
#include <sstream>

using namespace day_07_ns;

day_07::ParsedData day_07::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);

    day_07::ParsedData result;
    std::vector<std::string> dir_path;

    std::string line;
    std::getline(fin, line);

    while (true) {
        if(!line.length()) {
            if(!fin) {
                break;
            }
            std::getline(fin, line);
            continue;
        }
        if (line[0] != '$') {
            throw std::runtime_error("Expected a line starting with $, but got " + line);
        }
        std::string command = line.substr(2, 2);
        if (command == "cd") {
            std::string directory = line.substr(5);
            if (directory == "/") {
                dir_path.clear();
            } else if (directory == "..") {
                dir_path.pop_back();
            } else {
                dir_path.push_back(directory);
            }
            if(!fin) {
                break;
            }
            std::getline(fin, line);
            continue;
        }
        if (command != "ls") {
            throw std::runtime_error("Unknown command " + command);
        }
        auto current_dir = &result;
        for (auto dir_name: dir_path) {
            auto next_dir_iterator = current_dir->directories.find(dir_name);
            if (next_dir_iterator == current_dir->directories.end()) {
                throw std::runtime_error("No directory " + dir_name);
            }
            current_dir = &next_dir_iterator->second;
        }
        do {
            if(!fin) {
                break;
            }
            std::getline(fin, line);
            if (!line.length()) {
                continue;
            } 
            if (line[0] == '$') {
                break;
            }
            if (line.substr(0, 3) == "dir") {
                current_dir->directories.insert({line.substr(4), {{}, {}}});
            } else {
                std::istringstream ss(line);
                int64_t size;
                std::string filename;
                ss >> size >> filename;
                current_dir->files.insert({filename, size});
            }
        } while(true);

        if (!fin) {
            break;
        }

    }

    return result;
}

static std::pair<int64_t, int64_t> find_size_and_solve_part_1_result(const DirEntry& dir_entry, int64_t part_1_result) {
    int64_t current_size = 0;

    for (auto& [_, dir]: dir_entry.directories) {
        auto [dir_size, new_result] = find_size_and_solve_part_1_result(dir, part_1_result);
        part_1_result = new_result;
        current_size += dir_size;
    }
    for (auto& [_, file_size]: dir_entry.files) {
        current_size += file_size;
    }
    if (current_size < 100'000) {
        part_1_result += current_size;
    }
    return {current_size, part_1_result};
}

static std::pair<int64_t, int64_t> find_size_and_solve_part_2_result(
    const DirEntry& dir_entry, 
    int64_t min_size_to_delete
) {
    int64_t current_size = 0;
    int64_t part_2_result = 70'000'000;

    for (auto& [_, dir]: dir_entry.directories) {
        auto [dir_size, new_result] = find_size_and_solve_part_2_result(dir, min_size_to_delete);
        part_2_result = std::min(new_result, part_2_result);
        current_size += dir_size;
    }
    for (auto& [_, file_size]: dir_entry.files) {
        current_size += file_size;
    }
    if (current_size >= min_size_to_delete) {
        part_2_result = std::min(current_size, part_2_result);

    }
    return {current_size, part_2_result};
}

day_07::ResultData day_07::solve_part_1(const ParsedData& parsed_data) {
    auto [_, result] = find_size_and_solve_part_1_result(parsed_data, 0);
    return result;
}
day_07::ResultData day_07::solve_part_2(const ParsedData& parsed_data) {
    auto [total_size, _1] = find_size_and_solve_part_2_result(parsed_data, 0);
    int64_t min_deleted_space = total_size - 40'000'000;
    auto [_2, result] = find_size_and_solve_part_2_result(parsed_data, min_deleted_space);
    return result;
}

