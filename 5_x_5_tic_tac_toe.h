#ifndef _5_X_5_TIC_TAC_TOE_H
#define _5_X_5_TIC_TAC_TOE_H


#include <iostream>
#include <iomanip>
#include <cctype>  
#include "BoardGame_Classes.h"

using namespace std;

// 5x5 Tic Tac Toe Board
template <typename T>
class TicTacToeBoard : public Board<T> {
public:
    TicTacToeBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_draw();
    bool is_win() override;
    bool game_is_over() override;
    int count_three_in_row(T symbol);

    
    int get_n_moves() const;
};

template <typename T>
bool TicTacToeBoard<T>::is_win() {
    return count_three_in_row('X') > 0 || count_three_in_row('O') > 0;
}

template <typename T>
bool TicTacToeBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
class TicTacToePlayer : public Player<T> {
public:
    TicTacToePlayer(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class TicTacToeRandomPlayer : public RandomPlayer<T> {
public:
    TicTacToeRandomPlayer(T symbol);
    void getmove(int& x, int& y);
};

//----------------------------------------------------
// Implementation

template <typename T>
TicTacToeBoard<T>::TicTacToeBoard() {
    this->rows = this->columns = 5;
    this->board = new char*[5];
    for (int i = 0; i < 5; i++) {
        this->board[i] = new char[5];
        for (int j = 0; j < 5; j++) {
            this->board[i][j] = 0; 
        }
    }
    this->n_moves = 0;
}


template <typename T>
int TicTacToeBoard<T>::get_n_moves() const {
    return this->n_moves;
}

template <typename T>
bool TicTacToeBoard<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < 5 && y >= 0 && y < 5 && this->board[x][y] == 0) {
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void TicTacToeBoard<T>::display_board() {
    cout << "\n  ";
    for (int j = 0; j < 5; j++) {
        cout << setw(3) << j << " ";
    }
    cout << "\n";
    for (int i = 0; i < 5; i++) {
        cout << i << " ";
        for (int j = 0; j < 5; j++) {
            cout << "| " << (this->board[i][j] == 0 ? ' ' : this->board[i][j]) << " ";
        }
        cout << "|\n  ";
        for (int j = 0; j < 5; j++) {
            cout << "----";
        }
        cout << "-\n";
    }
}

template <typename T>
bool TicTacToeBoard<T>::is_draw() {
    return count_three_in_row('X') == count_three_in_row('O');
}

template <typename T>
int TicTacToeBoard<T>::count_three_in_row(T symbol) {
    int count = 0;
    // Check rows
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5 - 2; j++) {
            if (this->board[i][j] == symbol && this->board[i][j + 1] == symbol && this->board[i][j + 2] == symbol) {
                count++;
            }
        }
    }
    // Check columns
    for (int i = 0; i < 5 - 2; i++) {
        for (int j = 0; j < 5; j++) {
            if (this->board[i][j] == symbol && this->board[i + 1][j] == symbol && this->board[i + 2][j] == symbol) {
                count++;
            }
        }
    }
    // Check diagonals
    for (int i = 0; i < 5 - 2; i++) {
        for (int j = 0; j < 5 - 2; j++) {
            if (this->board[i][j] == symbol && this->board[i + 1][j + 1] == symbol && this->board[i + 2][j + 2] == symbol) {
                count++;
            }
        }
    }
    for (int i = 0; i < 5 - 2; i++) {
        for (int j = 2; j < 5; j++) {
            if (this->board[i][j] == symbol && this->board[i + 1][j - 1] == symbol && this->board[i + 2][j - 2] == symbol) {
                count++;
            }
        }
    }
    return count;
}

//----------------------------------------------------

template <typename T>
TicTacToePlayer<T>::TicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void TicTacToePlayer<T>::getmove(int& x, int& y) {
    cout << this->getname() << ", enter your move (row and column separated by space): ";
    cin >> x >> y;
}

template <typename T>
TicTacToeRandomPlayer<T>::TicTacToeRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {}

template <typename T>
void TicTacToeRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % 5; // Generate random row
    y = rand() % 5; // Generate random column
}

#endif