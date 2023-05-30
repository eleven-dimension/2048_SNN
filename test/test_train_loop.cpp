#include "../include/board.h"
#include "../include/pattern.h"
#include "../include/policy.h"

#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

string policy_play_one_game(Policy& policy)
{
    Board board(2048);
    board.reset_board_map();
    // board.print();

    string status = "play";

    int total_score = 0;
    while (status == "play")
    {
        // bool mask[4];
        // board.get_valid_action_mask(mask);

        // int move = board.random_valid_action(mask);
        // auto start = system_clock::now();

        auto [move, score, bit_map] = policy.get_best_action(board);

        // auto end = system_clock::now();
        // auto duration = duration_cast<microseconds>(end - start);
        // cout 
        //     << "time used: " 
        //     << double(duration.count()) * microseconds::period::num / microseconds::period::den
        //     << endl;

        auto pr = board.next_turn(move);

        total_score += pr.first;
        status = pr.second;

        cout << total_score << endl;
    }

    // cout << total_score << endl;
    // board.print();
    return status;
}

void evaluate_policy_play_games(Policy& policy, int game_num=1000)
{
    auto start = system_clock::now();
    
    int win_cnt = 0;
    for (int i = 0; i < game_num; i++)
    {
        string status = policy_play_one_game(policy);
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

void train_loop(
    int game_num,
    float learning_rate
)
{
    for (int game_cnt = 0; game_cnt < game_num; game_cnt++)
    {
        Board board(4096);
    }
}

int main()
{
    Policy policy;
    policy.add_pattern({0, 1, 4, 5, 8, 9});
    policy.add_pattern({1, 2, 5, 6, 9, 10});
    policy.add_pattern({0, 4, 8, 9, 12, 13});
    policy.add_pattern({1, 5, 9, 10, 13, 14});
    policy.add_pattern({2, 6, 10, 11, 14, 15});

    // evaluate_policy_play_games(policy);

    auto start = system_clock::now();

    string res = policy_play_one_game(policy);
    cout << res << endl;

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout 
        << "time used: " 
        << double(duration.count()) * microseconds::period::num / microseconds::period::den
        << endl;
}