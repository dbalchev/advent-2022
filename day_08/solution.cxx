#include <iostream>

#include <day_08.h>
#include <algorithm>
#include <iterator>


day_08::ParsedData day_08::parse_input(const char* filename) {
    auto fin = open_for_reading(filename);
    ParsedData result;
    std::copy(
        std::istream_iterator<std::string>(fin),
        std::istream_iterator<std::string>(),
        std::back_insert_iterator(result)
    );
    return result;
}

std::vector<std::vector<bool> > day_08::compute_left_visibility_mask(
    const day_08::ParsedData& tree_heights
) {
    std::vector<std::vector<bool> > result;
    result.reserve(tree_heights.size());
    for (auto& row_heights: tree_heights) {
        result.push_back({});
        auto &row_result = result.back();
        row_result.reserve(tree_heights.size());
        char highest_tree = '0' - 1;
        for (auto tree_height: row_heights) {
            row_result.push_back(tree_height > highest_tree);
            highest_tree = std::max(tree_height, highest_tree);
        }
    }
    return result;
}

std::vector<std::vector<bool> > day_08::compute_top_visibility_mask(
    const day_08::ParsedData& tree_heights
) {
    std::vector<std::vector<bool> > result;
    result.reserve(tree_heights.size());
    std::vector<char> highest_tree(tree_heights[0].size(), '0' - 1);
    for (auto& row_heights: tree_heights) {
        result.push_back({});
        auto &row_result = result.back();
        row_result.reserve(tree_heights.size());
        for (int i = 0; i < tree_heights.size(); ++i) {
            row_result.push_back(row_heights[i] > highest_tree[i]);
            highest_tree[i] = std::max(row_heights[i], highest_tree[i]);
        }
    }
    return result;
}

static int compute_visibility_and_update_stack(
    char tree_height,
    int i,
    std::vector< std::pair<char, int> > &highest_tree_stack
) {
    while (highest_tree_stack.size() && highest_tree_stack.back().first < tree_height) {
        highest_tree_stack.pop_back();
    }
    auto visible_index = highest_tree_stack.size() ? highest_tree_stack.back().second : 0;
    highest_tree_stack.push_back({tree_height, i});
    return visible_index;
}

std::vector<std::vector<int> > day_08::compute_left_visibility_distances(
    const day_08::ParsedData& tree_heights
) {
    std::vector<std::vector<int> > result;
    result.reserve(tree_heights.size());
    for (auto& row_heights: tree_heights) {
        result.push_back({});
        auto &row_result = result.back();
        row_result.reserve(tree_heights.size());
        std::vector< std::pair<char, int> > highest_tree_stack;
        for (int i = 0; i < row_heights.size(); ++i) {
            auto visible_index = compute_visibility_and_update_stack(
                row_heights[i],
                i,
                highest_tree_stack
            );
            row_result.push_back(i - visible_index);
        }
    }
    return result;
}

std::vector<std::vector<int> > day_08::compute_top_visibility_distances(
    const day_08::ParsedData& tree_heights
) {
    std::vector<std::vector<int> > result;
    result.reserve(tree_heights.size());
    std::vector<std::vector<std::pair<char, int> > > highest_tree_stacks(
        tree_heights[0].size(), std::vector<std::pair<char, int> >()
    );
    for (int row_index = 0; row_index < tree_heights.size(); ++row_index) {
        auto &row_heights = tree_heights[row_index];
        result.push_back({});
        auto &row_result = result.back();
        row_result.reserve(tree_heights.size());
        for (int i = 0; i < tree_heights.size(); ++i) {
            auto visible_index = compute_visibility_and_update_stack(
                row_heights[i],
                row_index,
                highest_tree_stacks[i]
            );
            row_result.push_back(row_index - visible_index);
        }
    }
    return result;
}

day_08::ResultData day_08::solve_part_1(const ParsedData& parsed_data) {
    auto temp_tree_heights = parsed_data;
    auto left_visibility_mask = compute_left_visibility_mask(temp_tree_heights);
    auto top_visibility_mask = compute_top_visibility_mask(temp_tree_heights);
    std::for_each(temp_tree_heights.begin(), temp_tree_heights.end(), [](auto &v){
        std::reverse(v.begin(), v.end());
    });
    auto right_visibility_mask = compute_left_visibility_mask(temp_tree_heights);
    std::for_each(right_visibility_mask.begin(), right_visibility_mask.end(), [](auto &v){
        std::reverse(v.begin(), v.end());
    });
    temp_tree_heights = parsed_data;
    std::reverse(temp_tree_heights.begin(), temp_tree_heights.end());
    auto bottom_visiblity_mask = compute_top_visibility_mask(temp_tree_heights);
    std::reverse(bottom_visiblity_mask.begin(), bottom_visiblity_mask.end());

    int num_visible_trees = 0;
    
    for (int i = 0; i < parsed_data.size(); ++i) {
        for (int j = 0; j < parsed_data[i].size(); ++j) {
            num_visible_trees += (
                left_visibility_mask[i][j] || right_visibility_mask[i][j] ||
                top_visibility_mask[i][j] || bottom_visiblity_mask[i][j]
            );
        }
    }
    return num_visible_trees;
}
day_08::ResultData day_08::solve_part_2(const ParsedData& parsed_data) {
    auto temp_tree_heights = parsed_data;
    auto left_visibility_distances = compute_left_visibility_distances(temp_tree_heights);
    auto top_visibility_distances = compute_top_visibility_distances(temp_tree_heights);
    std::for_each(temp_tree_heights.begin(), temp_tree_heights.end(), [](auto &v){
        std::reverse(v.begin(), v.end());
    });
    auto right_visibility_distances = compute_left_visibility_distances(temp_tree_heights);
    std::for_each(right_visibility_distances.begin(), right_visibility_distances.end(), [](auto &v){
        std::reverse(v.begin(), v.end());
    });
    temp_tree_heights = parsed_data;
    std::reverse(temp_tree_heights.begin(), temp_tree_heights.end());
    auto bottom_visiblity_distances = compute_top_visibility_distances(temp_tree_heights);
    std::reverse(bottom_visiblity_distances.begin(), bottom_visiblity_distances.end());

    int best_scenic_score = 0;
    
    for (int i = 0; i < parsed_data.size(); ++i) {
        for (int j = 0; j < parsed_data[i].size(); ++j) {
            int scenic_score = (
                left_visibility_distances[i][j] * right_visibility_distances[i][j] *
                top_visibility_distances[i][j] * bottom_visiblity_distances[i][j]
            );
            best_scenic_score = std::max(scenic_score, best_scenic_score);
        }
    }
    return best_scenic_score;
}

