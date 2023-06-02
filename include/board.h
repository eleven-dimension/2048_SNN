#pragma once

#include <bitset>
#include <iostream>
#include <string>

enum struct MoveDirection
{
    Up, Right, Down, Left
};

class Board
{
public:
    Board() = default;
    Board(const std::bitset<64>& board_map) {this->bit_map = board_map;};

    // operator
    Board& operator =(const Board& b) = default;
    bool operator ==(const Board& b) const { return this->bit_map == b.bit_map; }
    bool operator !=(const Board& b) const { return !(*this == b); }

    // set bitmap value
    void set_bitmap(const std::bitset<64>& board_map);

    // print board map
    void print();

    // get the board val (log_2 val) of a 4-bit tile
    int get_tile_val(int index);

    // set the board val of a 4-bit tile
    void set_tile_val(int index, int val);

    // convert row_bits (int) to int[]
    void convert_row_bits_to_arr(int rowbits, int row_arr[]);

    // convert int[] to (int)
    int convert_arr_to_row_bits(int row_arr[]);

    // get a row of the board
    int get_a_row(int row_index);

    // set a row of the board
    void set_a_row(int row_index, int row_bits);

    // generate one new tile
    void generate_one_new_tile();

    // reset board map
    void reset_board_map();

    // swap row and column of the board map
    void transpose();

    // row[i] <-> row[3 - i]
    void horizontal_reflection();

    // col[i] <-> col[3 - i]
    void vertical_reflection();

    // merge tiles in an array containing 4 tiles
    // direction is left
    // return the reward
    int merge_tiles(int tiles_val[]);

    // rotate clockwise
    void rotate_right();
    
    void rotate_left();

    // rotate clockwise for x times
    void rotate(int time);

    // shift to left
    // return the reward
    int shift_to_left();

    // four moves
    // return score
    int move_up();
    int move_right();
    int move_down();
    int move_left();

    // parameter: move direction enum
    int move_with_direction(MoveDirection move_direction);

    // member variable
    std::bitset<64> bit_map;
};