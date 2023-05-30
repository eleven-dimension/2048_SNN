#pragma once

#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <tuple>
#include <bitset>

#include "../include/board.h"
#include "../include/pattern.h"

class Policy
{
public:
    Policy() {};

    void add_pattern(std::vector<int> pattern_positions);
    float get_state_val(Board board);
    
    // return {action, action_val (= r + v(s'))}
    std::tuple<int, float, std::bitset<64>> get_best_action(Board board);

    // update table
    void update_pattern_table(
        Board board, float network_output_value, float state_target_value, float learning_rate
    );

    // variables
    std::vector<Pattern> patterns;
};
