#include <iostream>
#include "BoardGame_Classes.h"
#include "Pyramic_Tic-Tac-Toe.h"
#include "Word_Tic-Tac-Toe.h"
#include <fstream>
#include <limits>
using namespace std;

class clsInputValidate
{
public:
    static bool IsNumberBetween(int Number, int From, int To)
    {
        if (Number >= From && Number <= To)
            return true;
        else
            return false;
    }

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

    static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        int Number = ReadIntNumber();

        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadIntNumber();
        }
        return Number;
    }
};

int main()
{
    int choice;
    Player<char> *players[2];
    Word_Board<char> *B = new Word_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI Word Tic-Tac-Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    getline(cin, playerXName);
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    choice = clsInputValidate::ReadIntNumberBetween(1, 2);

    switch (choice)
    {
    case 1:
        players[0] = new Word_Player<char>(playerXName, '.');
        break;
    case 2:
        players[0] = new Word_Random_Player<char>('.');
        break;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin.ignore();
    getline(cin, player2Name);
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    choice = clsInputValidate::ReadIntNumberBetween(1, 2);
    switch (choice)
    {
    case 1:
        players[1] = new Word_Player<char>(player2Name, '.');
        break;
    case 2:
        players[1] = new Word_Random_Player<char>('.');
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return 1;
    }
    cin.ignore();
    // Create the game manager and run the game
    string fname;
    cout << "PLease Enter the name of the file to load words from:\n";
    cin >> fname;
    ifstream file(fname);
    while (!file.is_open())
    {
        cout << "Please Enter correct file name\n";
        cin >> fname;
        file.clear();
        file.open(fname);
    }
    string word;
    while (getline(file,word))
    {
        B->update_words(word);
    }
    file.close();
    GameManager<char> Word_game(B, players);
    Word_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }

    return 0;
}
