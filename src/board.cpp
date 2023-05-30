#include "../include/board.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>

using ull = unsigned long long;


void Board::print()
{
    std::cout << "-------board-------" << std::endl; 
    for (int i = 0; i < 16; i++)
    {
        int tile_val = get_tile_val(i);
        std::cout << std::left << std::setw(6) << (tile_val == 0 ? 0 : (1 << tile_val));
        if ((i + 1) % 4 == 0)
        {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

int Board::get_tile_val(int index)
{
    auto tile_val = (this->bit_map >> (index << 2)) & std::bitset<64>(0x0f);
    return int(tile_val.to_ulong());
}

void Board::set_tile_val(int index, int val)
{
    auto bit_map_after_0_setting = this->bit_map & std::bitset<64>(~(0x0fULL << (index << 2)));
    auto four_bit_val = std::bitset<64>(ull(val & 0x0f) << (index << 2));
    this->bit_map = bit_map_after_0_setting | four_bit_val;
}

// rowbits: 16 bit
void Board::convert_row_bits_to_arr(int rowbits, int row_arr[])
{
    for (int i = 0; i < 4; i++)
    {
        row_arr[i] = ((rowbits >> (i << 2)) & 0x0f);
    }
}

int Board::get_a_row(int row_index)
{
    auto bitset_row =  ((this->bit_map >> (row_index << 4)) & std::bitset<64>(0xffff));
    return int(bitset_row.to_ullong());
}

void Board::set_a_row(int row_index, int row_bits)
{
    this->bit_map = 
        (this->bit_map & std::bitset<64>(~(0xffffULL << (row_index << 4)))) | 
        std::bitset<64>(ull(row_bits & 0xffff) << (row_index << 4))
    ;
}


int Board::convert_arr_to_row_bits(int row_arr[])
{
    return row_arr[0] | (row_arr[1] << 4) | (row_arr[2] << 8) | (row_arr[3] << 12);
}


void Board::generate_one_new_tile()
{
    int empty_tile_index[16];
    int empty_tile_num = 0;

    for (int i = 0; i < 16; i++)
    {
        if (this->get_tile_val(i) == 0)
        {
            empty_tile_index[empty_tile_num++] = i;
        }
    }

    if (empty_tile_num)
    {
        int new_tile_val = (rand() % 10 ? 1 : 2);
        int new_tile_index = empty_tile_index[rand() % empty_tile_num];

        this->set_tile_val(new_tile_index, new_tile_val);
    }
}

void Board::reset_board_map()
{
    this->bit_map = 0;
    this->generate_one_new_tile();
    this->generate_one_new_tile();
}

void Board::transpose()
{
    this->bit_map = 
        (this->bit_map & std::bitset<64>(0xf0f00f0ff0f00f0fULL)) | 
        ((this->bit_map & std::bitset<64>(0x0000f0f00000f0f0ULL)) << 12) | 
        ((this->bit_map & std::bitset<64>(0x0f0f00000f0f0000ULL)) >> 12)
    ;
    this->bit_map = 
        (this->bit_map & std::bitset<64>(0xff00ff0000ff00ffULL)) | 
        ((this->bit_map & std::bitset<64>(0x00000000ff00ff00ULL)) << 24) | 
        ((this->bit_map & std::bitset<64>(0x00ff00ff00000000ULL)) >> 24)
    ;
}


void Board::vertical_reflection()
{
    this->bit_map = 
        ((this->bit_map & std::bitset<64>(0x000000000000ffffULL)) << 48) | 
        ((this->bit_map & std::bitset<64>(0x00000000ffff0000ULL)) << 16) |
        ((this->bit_map & std::bitset<64>(0x0000ffff00000000ULL)) >> 16) | 
        ((this->bit_map & std::bitset<64>(0xffff000000000000ULL)) >> 48)
    ;
}

void Board::horizontal_reflection()
{
    this->bit_map = 
        ((this->bit_map & std::bitset<64>(0x000f000f000f000fULL)) << 12) | 
        ((this->bit_map & std::bitset<64>(0x00f000f000f000f0ULL)) << 4) |
        ((this->bit_map & std::bitset<64>(0x0f000f000f000f00ULL)) >> 4) | 
        ((this->bit_map & std::bitset<64>(0xf000f000f000f000ULL)) >> 12)
    ;
}

int Board::merge_tiles(int tiles_val[])
{
    int tiles_val_index = 0;
    int last_tile_val = 0;
    int score = 0;

    for (int i = 0; i < 4; i++)
    {
        if (!tiles_val[i]) continue;

        if (last_tile_val == 0)
        {
            tiles_val[tiles_val_index++] = tiles_val[i];
            last_tile_val = tiles_val[i];
        }
        else
        {
            if (last_tile_val == tiles_val[i])
            {
                last_tile_val++;
                tiles_val[tiles_val_index - 1] = last_tile_val;
                score += (1 << last_tile_val);
            }
            else
            {
                tiles_val[tiles_val_index++] = tiles_val[i];
                last_tile_val = tiles_val[i];
            }
        }
    }

    for (int i = tiles_val_index; i < 4; i++)
    {
        tiles_val[i] = 0;
    }

    return score;
}

void Board::rotate_right()
{
    this->transpose();
    this->horizontal_reflection();
}

void Board::rotate_left()
{
    this->transpose();
    this->vertical_reflection();
}

void Board::rotate(int time)
{
    switch (((time % 4) + 4) % 4) 
    {
        default:
            case 0: 
                break;
            case 1: 
                rotate_right(); 
                break;
            case 2: 
                horizontal_reflection();
                vertical_reflection(); 
                break;
            case 3: 
                rotate_left(); 
                break;
    }
}

int Board::shift_to_left()
{
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        auto row_bits = this->get_a_row(i);
        int row_arr[4];
        this->convert_row_bits_to_arr(row_bits, row_arr);

        score += this->merge_tiles(row_arr);
        row_bits = this->convert_arr_to_row_bits(row_arr);
        this->set_a_row(i, row_bits);
    }
    return score;
}

std::pair<std::bitset<64>, int> Board::move_up()
{
    Board new_board;
    new_board.bit_map = this->bit_map;

    new_board.rotate_left();
    // move to left
    int score = new_board.shift_to_left();

    new_board.rotate_right();

    return {new_board.bit_map, score};
}

std::pair<std::bitset<64>, int> Board::move_right()
{
    Board new_board;
    new_board.bit_map = this->bit_map;

    new_board.horizontal_reflection();
    // move to left
    int score = new_board.shift_to_left();

    new_board.horizontal_reflection();

    return {new_board.bit_map, score};
}

std::pair<std::bitset<64>, int> Board::move_down()
{
    Board new_board;
    new_board.bit_map = this->bit_map;

    new_board.rotate_right();
    // move to left
    int score = new_board.shift_to_left();

    new_board.rotate_left();

    return {new_board.bit_map, score};
}


std::pair<std::bitset<64>, int> Board::move_left()
{
    Board new_board;
    new_board.bit_map = this->bit_map;

    // move to left
    int score = new_board.shift_to_left();

    return {new_board.bit_map, score};
}

// 0: up, 1: right, 2: down, 3: left
void Board::get_valid_action_mask(bool mask[])
{
    auto bit_map = this->move_up().first;
    mask[0] = !(bit_map == this->bit_map);

    bit_map = this->move_right().first;
    mask[1] = !(bit_map == this->bit_map);

    bit_map = this->move_down().first;
    mask[2] = !(bit_map == this->bit_map);

    bit_map = this->move_left().first;
    mask[3] = !(bit_map == this->bit_map);
}

// ensure mask not all False
int Board::random_valid_action(bool mask[])
{
    int valid_actions[4];
    int valid_action_num = 0;

    for (int i = 0; i < 4; i++)
    {
        if (mask[i])
        {
            valid_actions[valid_action_num++] = i;
        }
    }

    return valid_actions[rand() % valid_action_num];
}

// check lose
bool Board::check_lose()
{
    bool valid_action_mask[4];
    this->get_valid_action_mask(valid_action_mask);

    for (int i = 0; i < 4; i++)
    {
        if (valid_action_mask[i]) return false;
    }
    return true;
}

bool Board::check_win()
{
    for (int i = 0; i < 16; i++)
    {
        if ((1 << this->get_tile_val(i)) == this->max_tile) 
        {
            return true;
        }
    }
    return false;
}


std::pair<int, std::string> Board::next_turn(int action)
{
    int move_score = 0;
    if (action == 0)
    {
        auto [bit_map, score] = this->move_up();
        this->bit_map = bit_map;
        move_score = score;
    }
    else if (action == 1)
    {
        auto [bit_map, score] = this->move_right();
        this->bit_map = bit_map;
        move_score = score;
    }
    else if (action == 2)
    {
        auto [bit_map, score] = this->move_down();
        this->bit_map = bit_map;
        move_score = score;
    }
    else
    {
        auto [bit_map, score] = this->move_left();
        this->bit_map = bit_map;
        move_score = score;
    }
    
    if (this->check_win())
    {
        return {move_score, "win"};
    }

    this->generate_one_new_tile();
    bool lose_flag = this->check_lose();

    if (lose_flag)
    {
        return {move_score, "lose"};
    }
    return {move_score, "play"};
}
