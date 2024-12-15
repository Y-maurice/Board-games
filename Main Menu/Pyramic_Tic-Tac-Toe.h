#if !defined(_Pyramic_Tic_Tac_Toe_H)
#define _Pyramic_Tic_Tac_Toe_H

#include "BoardGame_Classes.h"

template <typename T>

class Pyramic_Board : public Board<T>
{
public:
    Pyramic_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Pyramic_Player : public Player<T>
{
public:
    Pyramic_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class Pyramic_Random_Player : public RandomPlayer<T>
{
public:
    Pyramic_Random_Player(T symbol);
    void getmove(int &x, int &y);
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;

template <typename T>
Pyramic_Board<T>::Pyramic_Board()
{
    this->rows = 3;
    this->columns = 5;
    this->board = new char *[3];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

bool IsValid(int x, int y)
{
    vector<pair<int, int>> validPairs = {{1, 3}, {2, 2}, {2, 3}, {2, 4}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}};
    for (int i = 0; i < validPairs.size(); i++)
    {
        if (validPairs[i].first == x and validPairs[i].second == y)
            return true;
    }
    return false;
}

template <typename T>
bool Pyramic_Board<T>::update_board(int x, int y, T symbol)
{
    if (IsValid(x, y) && this->board[x - 1][y - 1] == 0)
    {
        this->n_moves++;
        this->board[x - 1][y - 1] = toupper(symbol);
        return true;
    }
    else
        return false;
}

template <typename T>
void Pyramic_Board<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n";
        for (int j = 0; j < this->columns; j++)
        {
            if (IsValid(i + 1, j + 1))
            {
                cout << setw(3-i) << "" << "(" << i + 1 << "," << j + 1 << ")";
                cout << setw(2) << this->board[i][j] ;
            }
            else
            {
                cout << setw(6) << "";
            }
        }
        cout << "\n--------------------------------------------";
    }
    cout << endl;
}

template <typename T>
bool Pyramic_Board<T>::is_win()
{
    // Last row
    for (int j = 0; j < 3; j++)
    {
        if (this->board[2][j] == this->board[2][j + 1] && this->board[2][j + 1] == this->board[2][j + 2] && this->board[2][j] != 0)
            return true;
    }

    // 2nd row
    if (this->board[1][1] == this->board[1][2] && this->board[1][2] == this->board[1][3] && this->board[1][1] != 0)
        return true;

    // Column
    if (this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2] && this->board[0][2] != 0)
        return true;

    // Check diagonals
    if ((this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0) ||
        (this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4] && this->board[0][2] != 0))
    {
        return true;
    }

    return false;
}

template <typename T>
bool Pyramic_Board<T>::is_draw()
{
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Pyramic_Board<T>::game_is_over()
{
    return is_win() || is_draw();
}

//--------------------------------------

#include <limits>

static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again\n")
{
    int Number;
    while (!(cin >> Number))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << ErrorMessage;
    }
    return Number;
}

// Constructor for Pyramic_Player
template <typename T>
Pyramic_Player<T>::Pyramic_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Pyramic_Player<T>::getmove(int &x, int &y)
{
    cout << "\nPlease enter your move x and y (1 to 5) separated by spaces: ";
    x = ReadIntNumber();
    y = ReadIntNumber();
}

// Constructor for Pyramic_Random_Player
template <typename T>
Pyramic_Random_Player<T>::Pyramic_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
void Pyramic_Random_Player<T>::getmove(int &x, int &y)
{
    x = (rand() % this->dimension + 1); // Random number between 1 and 5
    y = (rand() % this->dimension + 1);
}

#endif // _Pyramic_Tic_Tac_Toe_H
