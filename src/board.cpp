#include "../include/board.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>

using ull = unsigned long long;

void Board::set_bitmap(const std::bitset<64>& board_map)
{
    this->bit_map = board_map;
}

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
                tiles_val[tiles_val_index - 1] = tiles_val[i] + 1;
                last_tile_val = 0;
                score += (1 << (tiles_val[i] + 1));
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

int Board::move_up()
{
    this->rotate_left();
    // move to left
    int score = this->shift_to_left();
    this->rotate_right();

    return score;
}

int Board::move_right()
{
    this->horizontal_reflection();
    // move to left
    int score = this->shift_to_left();
    this->horizontal_reflection();

    return score;
}

int Board::move_down()
{
    this->rotate_right();
    // move to left
    int score = this->shift_to_left();
    this->rotate_left();

    return score;
}


int Board::move_left()
{
    // move to left
    int score = this->shift_to_left();
    return score;
}

int Board::move_with_direction(MoveDirection move_direction)
{
    int score = 0;
    switch (move_direction)
    {
    case MoveDirection::Up:
        score = this->move_up();
        break;
    case MoveDirection::Right:
        score = this->move_right();
        break;
    case MoveDirection::Down:
        score = this->move_down();
        break;
    case MoveDirection::Left:
        score = this->move_left();
        break;
    }
    return score;
}
