#include <iostream>
#include <unordered_set>

#include <day_18.h>
using namespace day_18_ns;

day_18::ParsedData day_18::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    int x, y, z;
    char comma;
    ParsedData result;
    while (fin >> x >> comma >> y >> comma >> z) {
        result.push_back({x, y, z});
    }
    return result;
}

static const day_18::ParsedData deltas = {
    {1, 0, 0},
    {-1, 0, 0},
    {0, 1, 0},
    {0, -1, 0},
    {0, 0, 1},
    {0 ,0, -1},
};

template<>
struct std::hash<Cube> {
    std::size_t operator()(const Cube& p) const noexcept {
        auto [x, y, z] = p;
        return std::hash<int>{}(x) * 91 * 91 + std::hash<int>{}(y) * 91 + std::hash<int>{}(z);
    }
};

static std::vector<std::vector<std::vector<char> > >
make_volume(const day_18::ParsedData& parsed_data) {
    int max_x = 0, max_y = 0, max_z = 0;
    for (auto &[x, y, z]: parsed_data) {
        max_x = std::max(x, max_x);
        max_y = std::max(y, max_y);
        max_z = std::max(z, max_z);
    }
    std::vector<std::vector<std::vector<char> > > volume(
        (std::vector<char>::size_type)(max_x + 1),
        {(std::vector<char>::size_type)(max_y + 1), std::vector<char>(
            (std::vector<char>::size_type)(max_z + 1), 0
        )}
    );
    for (auto &[x, y, z]: parsed_data) {
        volume[x][y][z] = 1;
    }
    return volume;
}

day_18::ResultData day_18::solve_part_1(const ParsedData& parsed_data) {
    auto volume = make_volume(parsed_data);
    int max_x = volume.size() - 1;
    int max_y = volume[0].size() - 1;
    int max_z = volume[0][0].size() - 1;
    int num_sides = 0;
    for (auto &[x, y, z]: parsed_data) {
        for (auto &[dx, dy, dz]: deltas) {
            auto sx = dx + x;
            auto sy = dy + y;
            auto sz = dz + z;

            num_sides += (
                sx < 0 || sy < 0 || sz < 0 ||
                sx > max_x || sy > max_y | sz > max_z ||
                volume[sx][sy][sz] == 0
            );
        }
    }

    return num_sides;
}

day_18::ResultData day_18::solve_part_2(const ParsedData& parsed_data) {
    auto volume = make_volume(parsed_data);
    int max_x = volume.size() - 1;
    int max_y = volume[0].size() - 1;
    int max_z = volume[0][0].size() - 1;
    std::unordered_set<Cube> visited = {{-1, -1, -1}};
    std::vector<Cube> dfs_stack = {{-1, -1, -1}};
    while (!dfs_stack.empty()) {
        auto [x, y, z] = dfs_stack.back();
        dfs_stack.pop_back();
        for (auto &[dx, dy, dz]: deltas) {
            auto sx = dx + x;
            auto sy = dy + y;
            auto sz = dz + z;
            if (sx >= -1 && sy >= -1 && sz >= -1 &&
                sx <= max_x + 1 && sy <= max_y + 1 && sz <= max_z + 1 &&
                visited.count({sx, sy, sz}) == 0 &&
                (
                    sx < 0 || sy < 0 || sz < 0 ||
                    sx > max_x || sy > max_y | sz > max_z ||
                    volume[sx][sy][sz] == 0
                )
            ) {
                visited.insert({sx, sy, sz});
                dfs_stack.push_back({sx, sy, sz});    
            }
        }
    }
    int num_sides = 0;
    for (auto &[x, y, z]: parsed_data) {
        for (auto &[dx, dy, dz]: deltas) {
            auto sx = dx + x;
            auto sy = dy + y;
            auto sz = dz + z;

            num_sides += visited.count({sx, sy, sz}) && (
                sx < 0 || sy < 0 || sz < 0 ||
                sx > max_x || sy > max_y | sz > max_z ||
                volume[sx][sy][sz] == 0
            );
        }
    }

    return num_sides;
}

