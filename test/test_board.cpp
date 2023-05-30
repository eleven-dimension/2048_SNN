#include "../include/board.h"

#include <cstdlib>

void test_merge_tiles(Board board, int tiles[])
{
    int score = board.merge_tiles(tiles);

    for (int i = 0; i < 4; i++)
    {
        std::cout << tiles[i] << " ";
    }
    std::cout << std::endl;
    std::cout << score << std::endl;
}

void test_get_a_row(Board board, int row_index)
{
    std::cout << "test get a row" << std::endl;
    board.print();
    std::cout << row_index << std::endl;

    int v[4] = {0, 0, 0, 0};
    int row_bits = board.get_a_row(row_index);
    board.convert_row_bits_to_arr(row_bits, v);

    for (int i = 0; i < 4; i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    Board board;
    // srand(20000430);
    // srand(20000102);
    srand(19260817);

    // board.print();

    // board.reset_board_map();
    // board.print();

    // // test transpose
    // std::cout << "test transpose" << std::endl;

    // board.set_tile_val(0, 1);
    // board.set_tile_val(1, 2);
    // board.set_tile_val(3, 4);
    // board.set_tile_val(10, 12);
    // board.set_tile_val(15, 9);

    // board.print();

    // board.transpose();

    // board.print();

    // // test horizontal reflection
    // board.horizontal_reflection();
    // board.print();
    
    // // test vertical reflection
    // board.vertical_reflection();
    // board.print();

    // int a[4] = {1, 2, 2, 1};
    // test_merge_tiles(board, a);

    // int b[4] = {0, 0, 1, 1};
    // test_merge_tiles(board, b);

    // int c[4] = {2, 1, 2, 1};
    // test_merge_tiles(board, c);


    // test get a row
    board.set_tile_val(0, 1);
    board.set_tile_val(1, 1);
    board.set_tile_val(3, 4);
    board.set_tile_val(4, 1);
    board.set_tile_val(5, 1);
    board.set_tile_val(8, 3);
    board.set_tile_val(10, 3);
    board.set_tile_val(15, 2);
    // test_get_a_row(board, 0);
    // test_get_a_row(board, 1);
    // test_get_a_row(board, 2);
    // test_get_a_row(board, 3);

    // test set a row
    // auto row_bits = board.get_a_row(0);
    // Board board_a;
    // board_a.print();
    // board_a.set_a_row(1, row_bits);
    // board_a.print();

    // test convert row arr to int
    // Board board_a;
    // board_a.print();

    // int v[4] = {0, 3, 1, 2};
    // int row_bits = board_a.convert_arr_to_row_bits(v);
    // board_a.set_a_row(1, row_bits);

    // board_a.print();

    // board.test();

    // test move 
    board.print();
    auto [bit_map, score] = board.move_right();
    board.bit_map = bit_map;
    board.print();
    std::cout << score << std::endl;
}