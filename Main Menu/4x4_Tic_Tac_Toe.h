#ifndef TASK_2_PROBLEM_7_4X4_TIC_TAC_TOE_H
#define TASK_2_PROBLEM_7_4X4_TIC_TAC_TOE_H

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"

using namespace std;

int old_x,old_y;
template<class T>
class Board4x4:public Board<T>{
public:
    Board4x4();
    bool update_board(int x, int y, T symbol);
    bool is_valid(int x,int y,T symbol);
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
class Player4x4:public Player<T>{
public:
    Player4x4(string n, T symbol);
    Player4x4(T symbol); // For computer players

    void getmove(int& x, int& y);
};

template<class T>
class RandomPlayer4x4:public RandomPlayer<T>{

public:
    RandomPlayer4x4(T symbol);
    void getmove(int& x,int& y);
};



//-----------------Implementation---------------
template<class T>
Board4x4<T>::Board4x4() {
    this->rows = this->columns =4;
    this->board = new char*[this->rows];
    int cnt =0;
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            if (i==0||i==this->rows-1){
                if (cnt & 1){
                    this->board[i][j]='X';
                }
                else this->board[i][j] ='O';
                cnt++;
                if (cnt==4) cnt++;
            }
            else this->board[i][j] = 0;
        }
    }

    this->n_moves = 0;
}

template<class T>
void Board4x4<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n---------------------------------------";
    }
    cout << endl;
}

template<class T>
bool Board4x4<T>::is_valid(int x, int y,T symbol) {
    if(this->board[x][y] == 0 && this->board[old_x][old_y] == symbol && x>=0 && x<this->rows && y>=0 && y<this->columns
    &&((x == old_x -1 && y == old_y)||(x == old_x  && y == old_y-1)||
    (x == old_x && y == old_y+1)|| (x == old_x +1 && y == old_y))){
        return true;
    }
    return false;
}

template<class T>
bool Board4x4<T>::update_board(int x, int y, T symbol) {
    if (is_valid(x,y,symbol)){
        this->board[x][y]= symbol;
        this->board[old_x][old_y]=0;
        return true;
    }
    return false;
}


template<class T>
bool Board4x4<T>::check_rows() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < 2; j++) {
            bool win = true;
            auto x = this->board[i][j];
            if (x == 0) continue;
            for (int k = 0; k < 3; k++) {
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
bool Board4x4<T>::check_cols() {
    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j < 2; j++) {
            bool win = true;
            auto x = this->board[j][i];
            if (x == 0) continue;
            for (int k = 0; k < 3; k++) {
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
bool Board4x4<T>::check_diagonal_bottom_up() {
    for (int i = 2; i < this->rows; i++) {
        for (int j = 0; j < 2; j++) {
            auto x = this->board[i][j];
            bool win = true;
            if (x == 0) continue;
            for (int k = 0; k < 3; k++) {
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
bool Board4x4<T>::check_diagonal_up_bottom() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            auto x = this->board[i][j];
            bool win = true;
            if (x == 0) continue;
            for (int k = 0; k < 3; k++) {
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
bool Board4x4<T>::is_win() {
    return (check_rows() || check_cols() || check_diagonal_bottom_up() || check_diagonal_up_bottom());
}

template<class T>
bool Board4x4<T>::is_draw() {return false;}

template<class T>
bool Board4x4<T>::game_is_over() {return is_win();}

// Player implementation
template<class T>
Player4x4<T>::Player4x4(std::string n, T symbol):Player<T>(n,symbol) {}

template<class T>
Player4x4<T>::Player4x4(T symbol):Player<T>(symbol) {}


template<class T>
void Player4x4<T>::getmove(int &x, int &y) {
    cout<<"Enter the symbol you want to move\n";
    cin>>old_x>>old_y;
    cout<<"Enter the new Position\n";
    cin>>x>>y;
}

// Random Player implementation

template<class T>
RandomPlayer4x4<T>::RandomPlayer4x4(T symbol):RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));}

template<class T>
void RandomPlayer4x4<T>::getmove(int &x, int &y) {

    x = rand() % this->dimension;
    y = rand() % this->dimension;
    old_x = rand() % this->dimension;
    old_y = rand() % this->dimension;

}


#endif //TASK_2_PROBLEM_7_4X4_TIC_TAC_TOE_H
