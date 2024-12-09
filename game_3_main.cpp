#include <iostream>
#include "BoardGame_Classes.h"
#include "5_x_5_tic_tac_toe.h"

using namespace std;



int main() {
    Player<char>* players[2];
    TicTacToeBoard<char>* board = new TicTacToeBoard<char>();

    string name;
    int choice;

    cout << "Welcome to 5x5 Tic Tac Toe!\n";

    // Player selection
    for (int i = 0; i < 2; i++) {
        while (true) {
            cout << "Choose Player " << (i + 1) << " type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                cout << "Enter Player " << (i + 1) << " name: ";
                cin >> name;
                players[i] = new TicTacToePlayer<char>(name, (i == 0 ? 'X' : 'O'));
                break; 
            } else if (choice == 2) {
                players[i] = new TicTacToeRandomPlayer<char>((i == 0 ? 'X' : 'O'));
                break; 
            } else {
                cout << "Invalid choice. Please enter 1 or 2.\n";
            }
        }
    }

    int x, y;
    for (int turn = 0; turn < 25; turn++) {
        board->display_board();
        Player<char>* current_player = players[board->get_n_moves() % 2];// %2 so it will be only 0 or 1
        do {
            current_player->getmove(x, y);
        } while (!board->update_board(x, y, current_player->getsymbol()));
    }

    
    board->display_board();

    
    int x_score = board->count_three_in_row('X');
    int o_score = board->count_three_in_row('O');

    cout << players[0]->getname() << " (X) scored: " << x_score << " three-in-rows.\n";
    cout << players[1]->getname() << " (O) scored: " << o_score << " three-in-rows.\n";

    
    if (board->is_win()) {
        Player<char>* winner = x_score > o_score ? players[0] : players[1];
        cout << winner->getname() << " wins!\n";
    } else {
        cout << "It's a draw!\n";
    }

    
    delete board;
    delete players[0];
    delete players[1];
    return 0;
}







