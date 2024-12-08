#pragma once

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"

using namespace std;

template<class T>
class Numerical_Tic_Tac_Toe_Board : public Board<T> {
public:
    Numerical_Tic_Tac_Toe_Board();

    bool update_board(int x, int y, T symbol);

    /// Display the board and the pieces on it
    void display_board();

    /// Returns true if there is any winner
    bool is_win();

    /// Return true if all moves are done and no winner
    bool is_draw();

    /// Return true if the game is over
    bool game_is_over();

};

template<class T>
class Numerical_Tic_Tac_Toe_Player : public Player<T> {
public:
    Numerical_Tic_Tac_Toe_Player(string name, T symbol, vector<int> &available_numbers, bool is_odd);

    void getmove(int &x, int &y) override;

    bool hasNumber(int number);

    void removeNumber(int number);

private:
    vector<int> available_numbers;
    bool is_odd;

};


template<class T>
class Numerical_Tic_Tac_Toe_Random_Player : public RandomPlayer<T> {
public:
    Numerical_Tic_Tac_Toe_Random_Player(T symbol, vector<int> &available_numbers, bool is_odd);

    void getmove(int &x, int &y) override;

    bool hasNumber(int number);

    void removeNumber(int number);

private:
    vector<int> available_numbers;
    bool is_odd;
};
//--------------------------------Implementation----------------------------------

template<class T>
Numerical_Tic_Tac_Toe_Board<T>::Numerical_Tic_Tac_Toe_Board() {
    this->rows = 3;
    this->columns = 3;
    this->board = new T *[this->rows];

    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template<class T>
bool Numerical_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        return false;
    }
    if (this->board[x][y] == 0) {
        if (symbol == 0) {
            --this->n_moves;
            this->board[x][y] = 0;
        } else {
            ++this->n_moves;
            this->board[x][y] = toupper(symbol);
        }
        return true;
    }
    return false;
}

template<class T>
void Numerical_Tic_Tac_Toe_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ") ";
            cout << this->board[i][j] << " |";
        }
        cout << "\n---------------------------";
    }
    cout << endl;

}

template<class T>
bool Numerical_Tic_Tac_Toe_Board<T>::is_win() {

    for (int i = 0; i < this->rows; i++) {
        short sum_rows = 0, sum_cols = 0;
        for (int j = 0; j < this->columns; j++) {
            sum_cols += this->board[i][j];
            sum_rows += this->board[j][i];
        }
        if (sum_rows == 15 || sum_cols == 15) {
            return true;
        }
    }
    if ((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) ||
        (this->board[2][0] + this->board[1][1] + this->board[0][2] == 15)) {
        return true;
    }
    return false;

}

template<class T>
bool Numerical_Tic_Tac_Toe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<class T>
bool Numerical_Tic_Tac_Toe_Board<T>::game_is_over() {
    return (is_draw() || is_win());
}

//--------------------------Implementation player----------------------------
template<class T>
Numerical_Tic_Tac_Toe_Player<T>::Numerical_Tic_Tac_Toe_Player(string name, T symbol, vector<int> &available_numbers,
                                                              bool is_odd):Player<T>(name, symbol) {
    this->name = name;
    this->symbol = symbol;
    this->is_odd = is_odd;
    this->available_numbers = available_numbers;
}

template<class T>
bool Numerical_Tic_Tac_Toe_Player<T>::hasNumber(int number) {
    if (find(available_numbers.begin(), available_numbers.end(), number) != available_numbers.end()) {
        return true;
    }
    return false;
}

template<class T>
void Numerical_Tic_Tac_Toe_Player<T>::removeNumber(int number) {
    if (hasNumber(number)) {
        available_numbers.erase(remove(available_numbers.begin(), available_numbers.end(), number),
                                available_numbers.end());
    }
}

template<class T>
void Numerical_Tic_Tac_Toe_Player<T>::getmove(int &x, int &y) {
    cout << "Please enter X and Y (0,2):\n";
    cin >> x >> y;

    int z;
    do {
        cout << "enter the number you want to play from this list {";
        for (int i = 0; i < available_numbers.size(); ++i) {
            if (i!=available_numbers.size()-1){
                cout<<available_numbers[i]<<", ";
            }
            else{
                cout<<available_numbers[i]<<"}: \n";
            }
        }
        cin >> z;
    } while (find(available_numbers.begin(), available_numbers.end(), z) == available_numbers.end());
    this->symbol = z;
    removeNumber(z);

}



template<class T>
Numerical_Tic_Tac_Toe_Random_Player<T>::Numerical_Tic_Tac_Toe_Random_Player(T symbol, vector<int> &available_numbers,bool is_odd):RandomPlayer<T>(symbol) {
    this->symbol = symbol;
    this->is_odd = is_odd;
    this->available_numbers = available_numbers;
    srand(time(0));
}

template<class T>
bool Numerical_Tic_Tac_Toe_Random_Player<T>::hasNumber(int number) {
    if (find(available_numbers.begin(), available_numbers.end(), number) != available_numbers.end()) {
        return true;
    }
    return false;
}

template<class T>
void Numerical_Tic_Tac_Toe_Random_Player<T>::removeNumber(int number) {
    if (hasNumber(number)) {
        available_numbers.erase(remove(available_numbers.begin(), available_numbers.end(), number),
                                available_numbers.end());
    }
}

template<class T>
void Numerical_Tic_Tac_Toe_Random_Player<T>::getmove(int &x, int &y) {
    x = rand()%3;
    y = rand()%3;
    if (available_numbers.size()) {
        int index = rand() % available_numbers.size(), z = available_numbers[index];
        this->symbol = z;
        removeNumber(z);
    }else{
        this->symbol = available_numbers[0];
        removeNumber(available_numbers[0]);
    }

}
