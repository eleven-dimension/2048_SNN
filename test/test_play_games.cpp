#include "../include/board.h"

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

string play_one_game()
{
    Board board(2048);
    board.reset_board_map();
    // board.print();

    string status = "play";

    int total_score = 0;
    while (status == "play")
    {
        bool mask[4];
        board.get_valid_action_mask(mask);
        int move = board.random_valid_action(mask);
        auto pr = board.next_turn(move);

        total_score += pr.first;
        status = pr.second;
    }

    // cout << total_score << endl;
    // board.print();
    return status;
}

string play_one_game_by_human()
{
    Board board(16);
    board.reset_board_map();
    board.print();

    string status = "play";

    int total_score = 0;
    while (status == "play")
    {
        // bool mask[4];
        // board.get_valid_action_mask(mask);
        // int move = board.random_valid_action(mask);

        string move_input;
        int move;
        cin >> move_input;

        if (move_input == "up") move = 0;
        if (move_input == "right") move = 1;
        if (move_input == "down") move = 2;
        if (move_input == "left") move = 3;

        auto pr = board.next_turn(move);

        total_score += pr.first;
        status = pr.second;

        cout << "score: " << pr.first << endl;
        cout << "status: " << pr.second << endl;
        board.print();
    }

    cout << "game ends" << endl;
    cout << total_score << endl;
    board.print();
    cout << "status: " << status << endl;

    return status;
}

void test_randomly_play_games(int game_num=1000)
{
    auto start = system_clock::now();
    
    int win_cnt = 0;
    for (int i = 0; i < game_num; i++)
    {
        string status = play_one_game();
        if (status == "win")
        {
            win_cnt++;
        }
    }
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout 
        << "time used: " 
        << double(duration.count()) * microseconds::period::num / microseconds::period::den
        << endl;

    cout << "winning rate: " << win_cnt * 1.0 / game_num << endl;
}

int main()
{
    // play_one_game_by_human();
    test_randomly_play_games();
}