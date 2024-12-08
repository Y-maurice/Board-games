//
// Created by Michelle on 11/27/2024.
//
#include <iostream>
#include "BoardGame_Classes.h"
#include "4x4_Tic_Tac_Toe.h"

using namespace std;

int main() {
    int choice;
    Player<char>* players[2];
    Board4x4<char>* B = new Board4x4<char>;
    string playerXName, player2Name;

    cout << "Welcome to FCAI Four in a row Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new Player4x4<char>(playerXName, 'O');
            break;
        case 2:
            players[0] = new RandomPlayer4x4<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new Player4x4<char>(player2Name, 'X');
            break;
        case 2:
            players[1] = new RandomPlayer4x4<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    return 0;
}