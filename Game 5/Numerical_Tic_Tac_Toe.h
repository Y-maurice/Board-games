#pragma once
#include <iostream>
#include "BoardGame_Classes.h"

using namespace std;

template<class T>
class Numerical_Tic_Tac_Toe_Board:public Board<T>
{
public:
	Numerical_Tic_Tac_Toe_Board();

	bool update_board(int x, int y, T symbol) ;

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
class Numerical_Tic_Tac_Toe_Player:public Player<T>
{
public:
	Numerical_Tic_Tac_Toe_Player(string name, T symbol);
	void getmove(int& x, int& y);

};

template<class T>
class Numerical_Tic_Tac_Toe_Random_Player:public RandomPlayer<T>
{
public:
	Numerical_Tic_Tac_Toe_Random_Player(T symbol);
	void getmove(int& x, int& y);
};
//--------------------------------Implementation----------------------------------

template <class T>
Numerical_Tic_Tac_Toe_Board<T>::Numerical_Tic_Tac_Toe_Board()
{
	this->rows = 3;
	this->columns = 3;
	this->board = new T* [this->rows];

	for (int i = 0;i<this->rows;i++)
	{
		this->board[i] = new T* [this->columns];
		for (int j=0;j<this->columns;j++)
		{
			this->board[i][j] = 0;
		}
	}
	this->n_moves = 0;
}

template <class T>
bool Numerical_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T symbol)
{
	if (x<0 || x>= this->rows||y<0 || y >= this->columns)
	{
		return false;
	}
	if (this->board[x][y] == 0)
	{
		if (symbol == 0) {
			--this->n_moves;
			this->board[x][y] = 0;
		}
		else {
			++this->n_moves;
			this->board[x][y] = toupper(symbol);
		}
	}
}

template <class T>
void Numerical_Tic_Tac_Toe_Board<T>::display_board()
{
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

template <class T>
bool Numerical_Tic_Tac_Toe_Board<T>::is_win()
{
	
	for (int i =0 ;i<this->rows;i++)
	{
		short sum_rows = 0, sum_cols = 0;
		for (int j=0;j<this->columns;j++)
		{
			sum_cols += this->board[i][j];
			sum_rows += this->board[j][i];
		}
		if (sum_rows == 15 || sum_cols == 15)
		{
			return true;
		}
	}
	if ((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) || (this->board[2][0] + this->board[1][1] + this->board[0][2] == 15))
	{
		return true;
	}
	return false;

}

template <class T>
bool Numerical_Tic_Tac_Toe_Board<T>::is_draw()
{
	return (this->n_moves == 9 && !is_win());
}

template <class T>
bool Numerical_Tic_Tac_Toe_Board<T>::game_is_over()
{
	return (is_draw() || is_win());
}

//--------------------------Implementation player----------------------------
template <class T>
Numerical_Tic_Tac_Toe_Player<T>::Numerical_Tic_Tac_Toe_Player(string name, T symbol):Player<T>(name,symbol){}


template <class T>
void Numerical_Tic_Tac_Toe_Player<T>::getmove(int& x, int& y)
{
	cout << "\nPlease enter your move x (0 to 5) and y (0 to 6) separated by spaces: ";
	cin >> x >> y;
}


template <class T>
Numerical_Tic_Tac_Toe_Random_Player<T>::Numerical_Tic_Tac_Toe_Random_Player(T symbol):RandomPlayer<T>(symbol)
{
	this->dimension = 3;
	this->name = "Random Computer Player";
	srand(static_cast<unsigned int>(time(0)));
}

template<class T>
void Numerical_Tic_Tac_Toe_Random_Player<T>::getmove(int& x, int& y) {
	x = rand() % this->dimension;
	y = rand() % this->dimension;
}

