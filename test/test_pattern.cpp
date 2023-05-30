#include "../include/board.h"
#include "../include/pattern.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    Pattern p({0, 1, 2, 3, 4, 5});

    Board board;
    board.set_tile_val(0, 1);
    board.set_tile_val(1, 1);
    board.set_tile_val(3, 4);
    board.set_tile_val(4, 1);
    board.set_tile_val(5, 1);
    board.set_tile_val(8, 3);
    board.set_tile_val(10, 3);
    board.set_tile_val(15, 2);

    board.print();

    cout << p.get_pattern_value(board) << endl;

    p.update_pattern_value(board, 1.0, 0.1);

    cout << p.get_pattern_value(board) << endl;
}