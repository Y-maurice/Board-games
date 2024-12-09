#pragma once

#ifndef FOUR_IN_A_ROW_H
#define FOUR_IN_A_ROW_H

#include <iostream>
#include <iomanip>
#include "BoardGame_Classes.h"
using namespace std;

template<class T>
class Connect4_Board :public Board<T> {
public:
    Connect4_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool check_rows();
    bool check_cols();
    bool check_diagonal_bottom_up();
    bool check_diagonal_up_bottom();
    bool is_win();
    bool is_draw();
    bool game_is_over();

};


template<class T>
class Connect4_Player :public Player<T> {
public:
    Connect4_Player(string name, T symbol);
    void getmove(int& x, int& y);

};

template<class T>
class Connect4_Random_Player :public RandomPlayer<T> {
public:
    Connect4_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

///-------------------------IMPLEMENTATION-------------------
template<class T>
Connect4_Board<T>::Connect4_Board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new char* [this->rows];

    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template<class T>
bool Connect4_Board<T>::update_board(int x, int y, T mark) {
    // Check if x and y are within the valid range
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        return false;
    }

    // Check if the position is valid for placing a mark
    if (this->board[x][y] == 0 &&
        ((x == 0 && (x + 1 < this->rows && this->board[x + 1][y] != 0)) ||
            (x == this->rows - 1 && (x - 1 >= 0 && this->board[x - 1][y] == 0)) ||
            (x - 1 >= 0 && x + 1 < this->rows && this->board[x - 1][y] == 0 && this->board[x + 1][y] != 0))) {

        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}


template<class T>
void Connect4_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ") ";
            cout << this->board[i][j] << " |";
        }
        cout << "\n------------------------------------------------------------------";
    }
    cout << endl;
}

template<class T>
bool Connect4_Board<T>::check_rows() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < 4; j++) {
            bool win = true;
            auto x = this->board[i][j];
            if (x == 0) continue;
            for (int k = 0; k < 4; k++) {
                if (this->board[i][j + k] != x) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }
    return false;
}

template<class T>
bool Connect4_Board<T>::check_cols() {
    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j < 3; j++) {
            bool win = true;
            auto x = this->board[j][i];
            if (x == 0) continue;
            for (int k = 0; k < 4; k++) {
                if (this->board[j + k][i] != x ) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }
    return false;
}

// check if there are 4 coins connected from left bottom to right up
template<class T>
bool Connect4_Board<T>::check_diagonal_bottom_up() {
    for (int i = 3; i < this->rows; i++) {
        for (int j = 0; j < 4; j++) {
            auto x = this->board[i][j];
            bool win = true;
            if (x == 0) continue;
            for (int k = 0; k < 4; k++) {
                if (this->board[i - k][j + k] != x ) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }
    return false;
}

template<class T>
bool Connect4_Board<T>::check_diagonal_up_bottom() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            auto x = this->board[i][j];
            bool win = true;
            if (x == 0) continue;
            for (int k = 0; k < 4; k++) {
                if (this->board[i + k][j] != x ) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }
    return false;
}

template<class T>
bool Connect4_Board<T>::is_win() {
    return (check_rows() || check_cols() || check_diagonal_bottom_up() || check_diagonal_up_bottom());
}

template<class T>
bool Connect4_Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template<class T>
bool Connect4_Board<T>::game_is_over() {
    return (is_win() || is_draw());
}

//---------------------------Player implementation--------
template<class T>
Connect4_Player<T>::Connect4_Player(string name, T symbol) :Player<T>(name, symbol) {}

template<class T>
void Connect4_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x (0 to 5) and y (0 to 6) separated by spaces: ";
    cin >> x >> y;
}


template<class T>
Connect4_Random_Player<T>::Connect4_Random_Player(T symbol):RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template<class T>
void Connect4_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 6;
    y = rand() % 7;
}


#endif //FOUR_IN_A_ROW_H
