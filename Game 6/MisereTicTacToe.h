#pragma once

#include <iostream>
#include <iomanip>
#include <cctype> // For toupper()
#include "BoardGame_Classes.h" // Includes base classes like `Board` and `Player`

using namespace std;

//----------------------------------------------------
// Misere Tic Tac Toe Board (3x3)
template <typename T>
class MisereTicTacToeBoard : public Board<T> {
public:
    MisereTicTacToeBoard();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_draw() override;
    bool is_win() override;
    bool game_is_over() override;
};

template <typename T>
MisereTicTacToeBoard<T>::MisereTicTacToeBoard() {
    this->rows = this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0; // Initialize to empty
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool MisereTicTacToeBoard<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void MisereTicTacToeBoard<T>::display_board() {
    cout << "\n  ";
    for (int j = 0; j < this->columns; j++) {
        cout << setw(3) << j << " ";
    }
    cout << "\n";
    for (int i = 0; i < this->rows; i++) {
        cout << i << " ";
        for (int j = 0; j < this->columns; j++) {
            cout << "| " << (this->board[i][j] == 0 ? ' ' : this->board[i][j]) << " ";
        }
        cout << "|\n  ";
        for (int j = 0; j < this->columns; j++) {
            cout << "----";
        }
        cout << "-\n";
    }
}

template <typename T>
bool MisereTicTacToeBoard<T>::is_draw() {
    return this->n_moves == 9 && !is_win();
}

template <typename T>
bool MisereTicTacToeBoard<T>::is_win() {
    // Check rows and columns for three in a row
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true; // Losing condition (3 in a row)
        }
    }
    // Check diagonals for three in a row
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true; // Losing condition (3 in a row)
    }
    return false;
}

template <typename T>
bool MisereTicTacToeBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

//----------------------------------------------------
// Player Class for Misere Tic Tac Toe
template <typename T>
class MisereTicTacToePlayer : public Player<T> {
public:
    MisereTicTacToePlayer(string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
MisereTicTacToePlayer<T>::MisereTicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void MisereTicTacToePlayer<T>::getmove(int& x, int& y) {
    cout << this->getname() << ", enter your move (row and column): ";
    cin >> x >> y;
}

//----------------------------------------------------
// Random Player Class for Misere Tic Tac Toe
template <typename T>
class MisereTicTacToeRandomPlayer : public RandomPlayer<T> {
public:
    MisereTicTacToeRandomPlayer(T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
MisereTicTacToeRandomPlayer<T>::MisereTicTacToeRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {}

template <typename T>
void MisereTicTacToeRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % 3;
    y = rand() % 3;
}
