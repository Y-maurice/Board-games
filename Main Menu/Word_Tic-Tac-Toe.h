#if !defined(_Word_Tic_Tac_Toe_H)
#define _Word_Tic_Tac_Toe_H
#include "BoardGame_Classes.h"
#include <vector>


template <typename T>
class Word_Board:public Board<T> {
private:
    vector <string> words;
public:
    Word_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    void update_words(string word)
    {
        words.push_back(word);
    }
};

template <typename T>
class Word_Player : public Player<T> {
public:
    Word_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Word_Random_Player : public RandomPlayer<T> {
public:
    Word_Random_Player (T symbol);
    void getmove(int &x, int &y);
};


//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>
#include <fstream>
using namespace std;


template<typename T>

Word_Board<T>::Word_Board()
{
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
bool Word_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x-1 < 0 || x-1 >= this->rows || y-1 < 0 || y-1 >= this->columns)) {
        this->n_moves++;
        this->board[x-1][y-1] = toupper(mark);
        return true;
    }
    return false;
}



template <typename T>
void Word_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i+1 << "," << j+1 << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}



bool Rec(int l,int r,vector<string> words,string word) 
{
    if(l > r)
        return false;
    int curr = (l + r) / 2;
    if(words[curr] == word)
        return true;
    else if(words[curr] < word)
        return Rec(curr+1,r,words,word);
    else
        return Rec(l,curr-1,words,word);
}


template <typename T>
bool Word_Board<T>::is_win() {
    string curr_word;
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if (this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0)
        {
            for (int k = 0; k < 3; ++k) {
                curr_word += this->board[i][k];
            }
            if(Rec(0,this->words.size(),this->words,curr_word)) 
                return true;
            curr_word = "";   
        }
        else if (this->board[0][i] != 0 && this->board[1][i] != 0 && this->board[2][i] != 0)
        {
            for (int k = 0; k < 3; ++k) {
                curr_word += this->board[k][i];
            }
            if(Rec(0,this->words.size(),this->words,curr_word)) 
                return true;
            curr_word = "";  
        }
    }

    // Check diagonals
    if (this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0)
    {
        for (int k = 0; k < 3; ++k) {
            curr_word += this->board[k][k];
        }  
        if(Rec(0,this->words.size(),this->words,curr_word)) 
            return true;
        curr_word = "";       
    }
    else if (this->board[0][2] != 0 && this->board[1][1] != 0 && this->board[2][0] != 0) 
    {
        curr_word += this->board[0][2];
        curr_word += this->board[1][1];
        curr_word += this->board[2][0];
        if(Rec(0,this->words.size(),this->words,curr_word)) 
            return true;
        curr_word = "";         
    }
    return false;
}

template <typename T>
bool Word_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Word_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
Word_Player<T>::Word_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Word_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease Enter your move x and y (1 to 3) separated by spaces: ";
    cin >> x >> y;
    cout << "\nPlease Enter the letter you want to place: \n";
    cin >> this->symbol;
}


template <typename T>
Word_Random_Player<T>::Word_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

}

template <typename T>
void Word_Random_Player<T>::getmove(int& x, int& y) {
    x = (rand() % this->dimension + 1);  // Random number between 1 and 3
    y = (rand() % this->dimension + 1);
    this->symbol = char(rand() % 26 + 65); // Generates random character from A-Z
}

#endif // _Word_Tic_Tac_Toe_H
