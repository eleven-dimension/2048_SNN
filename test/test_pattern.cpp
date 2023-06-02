#include "../include/board.h"
#include "../include/pattern.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    // test iso
    {
        std::cout << "test iso" << std::endl;
        Pattern p({0, 1, 2, 3, 4, 5});

        for (int i = 0; i < 8; i++)
        {
            for (auto& x : p.pattern_positions[i])
            {
                cout << x << " ";
            }
            cout << endl;
        }
    }

    // test save
    {
        std::cout << "test save" << std::endl;
        Pattern p({ 0, 1, 2, 3, 4, 5 });
        p.save_table("../model/model.txt");
        p.load_table("../model/model.txt");
    }

    // test update value
    {
        std::cout << "update value" << std::endl;

        Pattern p({ 0, 1, 2, 3, 4, 5 });

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

        p.update_pattern_value(board, 1.0);

        cout << p.get_pattern_value(board) << endl;

        cout << MultiArrayAt(p.table, 0, 3, 1, 1, 0, 0) << endl;
        cout << MultiArrayAt(p.table, 1, 1, 0, 4, 1, 1) << endl;
    }
}