#include "../include/board.h"
#include "../include/pattern.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <array>

// vector<int>(6)
Pattern::Pattern(std::vector<int> chosen_positions)
{
    this->chosen_positions = chosen_positions;
    this->table = {0};
}

float Pattern::get_pattern_value(Board& board)
{
    std::vector<int> table_index(6, 0);
    for (int i = 0; i < 6; i++)
    {
        auto board_val = board.get_tile_val(this->chosen_positions[i]);
        table_index[i] = board_val;
    }
    // for (auto x : table_index)
    // {
    //     std::cout << x << " ";
    // }
    // std::cout << std::endl;

    return this->table[
        table_index[0]
    ][
        table_index[1]
    ][
        table_index[2]
    ][
        table_index[3]
    ][
        table_index[4]
    ][
        table_index[5]
    ];
}

void Pattern::update_pattern_value(Board& board, float target_value, float learning_rate)
{
    std::vector<int> table_index(6, 0);
    for (int i = 0; i < 6; i++)
    {
        auto board_val = board.get_tile_val(this->chosen_positions[i]);
        table_index[i] = board_val;
    }

    auto& table_grid_ref = this->table[
        table_index[0]
    ][
        table_index[1]
    ][
        table_index[2]
    ][
        table_index[3]
    ][
        table_index[4]
    ][
        table_index[5]
    ];

    float new_table_value = (1 - learning_rate) * table_grid_ref + learning_rate * target_value;
    table_grid_ref = new_table_value;
}