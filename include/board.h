#pragma once

#include <bitset>
#include <iostream>
#include <string>

class Board
{
public:
    Board() { this->max_tile = 4096;};
    Board(int max_tile_val) { this->max_tile = max_tile_val; };

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
    // return pair<board state, score>
    std::pair<std::bitset<64>, int> move_up();
    std::pair<std::bitset<64>, int> move_right();
    std::pair<std::bitset<64>, int> move_down();
    std::pair<std::bitset<64>, int> move_left();

    // valid action mask
    void get_valid_action_mask(bool mask[]);

    // [0, 3]
    int random_valid_action(bool mask[]);

    // check lose
    bool check_lose();

    // check win
    bool check_win();

    // member var
    std::bitset<64> bit_map;
    int max_tile;

    // env step
    // action: [0, 3]
    std::pair<int, std::string> next_turn(int action);
};