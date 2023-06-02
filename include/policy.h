#pragma once

#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <tuple>
#include <bitset>

#include "../include/board.h"
#include "../include/pattern.h"
#include "../include/move.h"


class Policy
{
public:
    Policy() {};

    void add_pattern(std::array<int, 6> pattern_positions);
    float get_state_val(Board& board);
    
    // return {action, action_val (= r + v(s'))}
    Move get_best_action(Board& board);

    // update table
    float update_pattern_table(Board& board, float adjust);

    void learn_from_episode(std::vector<Move>& path, float alpha = 0.05);

    // member variables
    std::vector<Pattern> patterns;
};
