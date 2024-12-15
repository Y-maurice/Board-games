#if !defined(_Ultimate_Tic_Tac_Toe_H)
#define _Ultimate_Tic_Tac_Toe_H

#include "BoardGame_Classes.h"

template <typename T>
class Ultimate_Board:public Board<T> {
private:
 int n_moves;
    char is_mini_win(int Xi,int Yi);
public:
    Ultimate_Board ();
    int get_n_moves();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Ultimate_Player : public Player<T> {
public:
    Ultimate_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};


template <typename T>
class Ultimate_Random_Player : public RandomPlayer<T>{
public:
    Ultimate_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};


//--------------------------------------- IMPLEMENTATION


#include <iostream>
#include <iomanip>
#include <cctype> 
using namespace std;

template <typename T>
int Ultimate_Board<T> :: get_n_moves(){
    return n_moves;
}

template <typename T>
Ultimate_Board<T>::Ultimate_Board() {
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}





template <typename T>
bool Ultimate_Board<T>::update_board(int x, int y, T mark) {
    if (!(x-1 < 0 || x-1 >= this->rows || y-1 < 0 || y-1 >= this->columns)  && this->board[x - 1][y - 1] == 0)
    {
        this->n_moves++;
        this->board[x - 1][y - 1] = toupper(mark);
        return true;
    }
    else
        return false;
}


template <typename T>
void Ultimate_Board<T>::display_board() {
    for (int Xi = 0; Xi < 9; Xi += 3) { 
        for (int i = Xi; i < Xi + 3; i++) { 
            for (int j = 0; j <= 6; j += 3) { 
                for (int k = j; k < j + 3; k++) { 
                    cout << "(" << i + 1 << "," << k + 1 << ")"; 
                    cout << setw(2) << this->board[i][k] << " "; 
                }
                cout << "   "; 
            }
            cout << endl; 
        }
        cout << "-----------------------------------------------------------------------------\n";
    }
}


template <typename T>
char Ultimate_Board<T>::is_mini_win(int Xi,int Yi) {

    bool flag = false;
    char symbol = 0;
    // Check rows
    for (int i = Xi; i < Xi + 3; i++) {
        if (this->board[i][Yi] == this->board[i][Yi+1] && this->board[i][Yi+1] == this->board[i][Yi+2] && this->board[i][Yi] != 0) {
            flag = true;
            symbol = this->board[i][Yi];
            break;
        }
    }
    // Check columns
    for (int i = Yi; i < Yi+3; i++)
    {
        if(this->board[Xi][i] == this->board[Xi+1][i] && this->board[Xi+1][i] == this->board[Xi+2][i] && this->board[Xi][i] != 0)
        {
            flag = true;
            symbol = this->board[Xi][i];
            break;
        }
    }
    

    // Check diagonals
    if ((this->board[Xi][Yi] == this->board[Xi+1][Yi+1] && this->board[Xi+1][Yi+1] == this->board[Xi+2][Yi+2] && this->board[Xi][Yi] != 0) ||
        (this->board[Xi][Yi+2] == this->board[Xi+1][Yi+1] && this->board[Xi+1][Yi+1] == this->board[Xi+2][Yi] && this->board[Xi][Yi+2] != 0)) {
        symbol = this->board[Xi+1][Yi+1];
        flag = true;
    }
    
    if(flag)
    {
        for (int i = Xi; i < Xi + 3; i++)
        {
            for (int j = Yi; j < Yi + 3; j++)
            {
                this->board[i][j] = symbol;
            }
        }
        return symbol;
    }
    return symbol;
}



// Returns true if there is any winner
template <typename T>
bool Ultimate_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i <= 6; i += 3) {
        if(is_mini_win(i,0) == is_mini_win(i,3) && is_mini_win(i,3) == is_mini_win(i,6) && is_mini_win(i,0) != 0 ||
        is_mini_win(0,i) == is_mini_win(3,i) && is_mini_win(3,i) == is_mini_win(6,i) && is_mini_win(0,i) != 0)
        {
            return true;
        }
    }
    // Check diagonals
    if(is_mini_win(0,0) == is_mini_win(3,3) && is_mini_win(3,3) == is_mini_win(6,6) && is_mini_win(0,0) != 0 ||
    is_mini_win(0,6) == is_mini_win(3,3) && is_mini_win(3,3) == is_mini_win(6,0) && is_mini_win(0,6) != 0 ) 
    {
        return true;
    }

    return false;
}


template <typename T>
bool Ultimate_Board<T>::is_draw() {
    return (this->n_moves == 81 && !is_win());
}

template <typename T>
bool Ultimate_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
Ultimate_Player<T>::Ultimate_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Ultimate_Player<T>::getmove(int& x, int& y) {
    cout << this->name << "'s turn (" << this->symbol << "). Enter coordinates (row col): ";
    cin >> x >> y;
}

// Implementation for Ultimate_Random_Player
template <typename T>
Ultimate_Random_Player<T>::Ultimate_Random_Player(T symbol) : RandomPlayer<T>(symbol) {}

template <typename T>
void Ultimate_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 9 + 1;
    y = rand() % 9 + 1;
}


#endif // _Ultimate_Tic_Tac_Toe_H