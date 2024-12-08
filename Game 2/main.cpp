//
// Created by Michelle on 11/27/2024.
//
#include <iostream>
#include "BoardGame_Classes.h"
#include "Numerical_Tic_Tac_Toe.h"

using namespace std;

int main() {
    int playerType, numType;
    bool is_odd;
    Player<int> *players[2];
    Numerical_Tic_Tac_Toe_Board<int> *B = new Numerical_Tic_Tac_Toe_Board<int>;
    string playerXName, player2Name;

    cout << "Welcome to FCAI Numerical Tic Tac Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player 1 name: ";
    cin >> playerXName;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> playerType;
    cout << "Choose the number type you want to play with\n"
            "1. Odd\n"
            "2. Even\n";
    cin >> numType;


    vector<int> oddAvailableNums = {1, 3, 5, 7, 9}, evenAvailableNums = {2, 4, 6, 8};

    switch (playerType) {
        case 1:
            switch (numType) {
                case 1:
                    is_odd = true;
                    players[0] = new Numerical_Tic_Tac_Toe_Player<int>(playerXName, 0, oddAvailableNums, true);
                    break;
                case 2:
                    is_odd = false;
                    players[0] = new Numerical_Tic_Tac_Toe_Player<int>(playerXName, 0, evenAvailableNums, false);
                    break;
            }
            break;
        case 2:
            switch (numType) {
                case 1:
                    is_odd = true;
                    players[0] = new Numerical_Tic_Tac_Toe_Random_Player<int>(0, oddAvailableNums, true);
                    break;
                case 2:
                    is_odd = false;
                    players[0] = new Numerical_Tic_Tac_Toe_Random_Player<int>(0, evenAvailableNums, false);
                    break;
            }
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> playerXName;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> playerType;

    is_odd = !is_odd;
    switch (playerType) {
        case 1:
            if (is_odd) players[1] = new Numerical_Tic_Tac_Toe_Player<int>(playerXName, 0, oddAvailableNums, true);
            else players[1] = new Numerical_Tic_Tac_Toe_Player<int>(playerXName, 0, evenAvailableNums, false);
            break;
        case 2:
            if (is_odd) players[1] = new Numerical_Tic_Tac_Toe_Random_Player<int>(0, oddAvailableNums, true);
            else players[1] = new Numerical_Tic_Tac_Toe_Random_Player<int>(0, evenAvailableNums, false);
            break;
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<int> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    return 0;
}