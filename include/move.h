#pragma once

#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

#include "../include/board.h"

class Move
{
public:
    Move();
    Move(MoveDirection direction);
    Move(Board& board, MoveDirection direction);

    void initialize(Board& board);

    bool is_valid();

    bool check_win();
    
    // member variable
    Board before_board;
    Board after_board;
    MoveDirection direction;
    int score;
    float move_value;
};