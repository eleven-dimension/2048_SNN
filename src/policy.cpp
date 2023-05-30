#include "../include/board.h"
#include "../include/pattern.h"
#include "../include/policy.h"

#include <vector>
#include <iostream>

void Policy::add_pattern(std::vector<int> pattern_positions)
{
    Pattern p(pattern_positions);
    this->patterns.emplace_back(p);
}

float Policy::get_state_val(Board board)
{
    // rotate * 4
    float val = 0;
    for (int time = 0; time < 4; time++)
    {
        board.rotate(time);
        for (auto& pattern : this->patterns)
        {
            val += pattern.get_pattern_value(board);
        }
    }

    // mirror + rotate
    board.horizontal_reflection();
    for (int time = 0; time < 4; time++)
    {
        board.rotate(time);
        for (auto& pattern : this->patterns)
        {
            val += pattern.get_pattern_value(board);
        }
    }

    return val;
}


std::tuple<int, float, std::bitset<64>> Policy::get_best_action(Board board)
{
    bool valid_action_mask[4];
    board.get_valid_action_mask(valid_action_mask);

    float best_action_val = -1e8;
    int best_action = 0;
    std::bitset<64> best_afterstate;

    for (int action = 0; action < 4; action++)
    {
        if (!valid_action_mask[action])
        {
            continue;
        }
        
        std::pair<std::bitset<64>, int> result;

        if (action == 0)
        {
            result = board.move_up();
        }
        else if (action == 1)
        {
            result = board.move_right();
        }
        else if (action == 2)
        {
            result = board.move_down();
        }
        else
        {
            result = board.move_left();
        }

        std::bitset<64> new_board_map = result.first;
        int merge_score = result.second;

        // S'
        Board new_board;
        new_board.bit_map = new_board_map;
        float afterstate_val = this->get_state_val(new_board);
        if (merge_score + afterstate_val > best_action_val)
        {
            best_action = action;
            best_action_val = merge_score + afterstate_val;
            best_afterstate = new_board_map;
        }
    }

    return {best_action, best_action_val, best_afterstate};
}


void Policy::update_pattern_table(
    Board board, float network_output_value, 
    float state_target_value, float learning_rate
)
{
    int pattern_num = this->patterns.size() * 8;
    float pattern_target_value = state_target_value / pattern_num;

    // rotate * 4
    for (int time = 0; time < 4; time++)
    {
        board.rotate(time);
        for (auto& pattern : this->patterns)
        {
            pattern.update_pattern_value(board, pattern_target_value, learning_rate);
        }
    }

    // mirror + rotate
    board.horizontal_reflection();
    for (int time = 0; time < 4; time++)
    {
        board.rotate(time);
        for (auto& pattern : this->patterns)
        {
            pattern.update_pattern_value(board, pattern_target_value, learning_rate);
        }
    }
}