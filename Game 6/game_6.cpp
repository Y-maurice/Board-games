#include <iostream>
#include "MisereTicTacToe.h"
#include "BoardGame_Classes.h" // Includes base classes like `Board` and `Player`

using namespace std;


int main() {
    Player<char>* players[2];
    MisereTicTacToeBoard<char>* board = new MisereTicTacToeBoard<char>();

    string name;
    int choice;

    cout << "Welcome to Misere Tic Tac Toe!\n";

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
                players[i] = new MisereTicTacToePlayer<char>(name, (i == 0 ? 'X' : 'O'));
                break;
            } else if (choice == 2) {
                players[i] = new MisereTicTacToeRandomPlayer<char>((i == 0 ? 'X' : 'O'));
                break;
            } else {
                cout << "Invalid choice. Please enter 1 or 2.\n";
            }
        }
    }

    // Main game loop
    int turn = 0;
    while (!board->game_is_over()) {
        board->display_board();
        Player<char>* current_player = players[turn % 2];
        int x, y;
        do {
            current_player->getmove(x, y);
        } while (!board->update_board(x, y, current_player->getsymbol()));

        if (board->is_win()) {
            cout << current_player->getname() << " loses!\n";
            break;
        }

        turn++;
        if (board->is_draw()) {
            cout << "It's a draw!\n";
            break;
        }
    }

    board->display_board();

    // Cleanup
    delete board;
    delete players[0];
    delete players[1];

    return 0;
}




