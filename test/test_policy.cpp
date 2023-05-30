#include "../include/board.h"
#include "../include/pattern.h"
#include "../include/policy.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    Policy policy;
    policy.add_pattern({0, 1, 4, 5, 8, 9});
    policy.add_pattern({1, 2, 5, 6, 9, 10});
    policy.add_pattern({0, 4, 8, 9, 12, 13});
    policy.add_pattern({1, 5, 9, 10, 13, 14});
    policy.add_pattern({2, 6, 10, 11, 14, 15});


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

    // cout << policy.get_state_val(board);

    auto [action, value, afterstate] = policy.get_best_action(board);
    cout << action << endl;
    cout << value << endl;
}