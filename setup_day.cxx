#include <iostream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <fstream>
#include <gflags/gflags.h>
#include <regex>

DEFINE_int32(day, -1, "Which day to add");

static std::string make_day_no_as_string(int day) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << day;
    return ss.str();
}


int main(int argc, char** argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    int day = FLAGS_day;
    std::string day_no_as_string = make_day_no_as_string(day);
    std::string day_name = "day_" + day_no_as_string;
    std::regex day_00_regex("day_00");

    bool dir_created = std::filesystem::create_directories(day_name + "/" + "include");
    if (!dir_created) {
        std::cerr << "Cannot create " << day_name << std::endl;
        return 1;
    }
    for (const auto &dir_entry: std::filesystem::recursive_directory_iterator("day_00")) {
        std::cout << dir_entry.path() << " " << dir_entry.is_directory() << " " << dir_entry.is_regular_file() << std::endl;
        std::ifstream reader(dir_entry.path());
        std::ofstream writer(std::regex_replace(dir_entry.path().string(), day_00_regex, day_name));

        while (reader) {
            std::string buffer;
            std::getline(reader, buffer);
            buffer = std::regex_replace(buffer, day_00_regex, day_name);
            writer << buffer << std::endl;
        }
    }
    {
        std::ifstream reader("main.cxx");
        std::ofstream writer("main.cxx.0");

        while (reader) {
            std::string buffer;
            std::getline(reader, buffer);
            if (buffer.find("// Add include above this line") != std::string::npos) {
                writer << "#include <" << day_name << ".h>" << std::endl;
            } else if (buffer.find("// Add solution function above this line") != std::string::npos) {
                auto num_spaces = buffer.find_first_not_of(' ');
                writer << std::string(num_spaces, ' ') << "{" << day << ", " << day_name << "::solution}," << std::endl;
            }
            writer << buffer << std::endl;
        }
    }
    std::filesystem::remove("main.cxx");
    std::filesystem::rename("main.cxx.0", "main.cxx");
    std::filesystem::last_write_time("CMakeLists.txt", std::filesystem::file_time_type::clock::now());
    return 0;
}
