#include <iostream>
#include "cls_input_validate.h"
#include "Pyramic_Tic-Tac-Toe.h"   // 1
#include "Connect4.h"              //2
#include "5_x_5_tic_tac_toe.h"     //3
#include "Word_Tic-Tac-Toe.h"      //4
#include "Numerical_Tic_Tac_Toe.h" //5
#include "MisereTicTacToe.h"       //6
#include "4x4_Tic_Tac_Toe.h"       //7
#include "Ultimate_Tic_Tac_Toe.h"  //8
using namespace std;

int game_1()
{
    int choice;
    Player<char> *players[2];
    Pyramic_Board<char> *B = new Pyramic_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to Pyramic X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[0] = new Pyramic_Player<char>(playerXName, 'X');
        break;
    case 2:
        players[0] = new Pyramic_Random_Player<char>('X');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[1] = new Pyramic_Player<char>(player2Name, 'O');
        break;
    case 2:
        players[1] = new Pyramic_Random_Player<char>('O');
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return 1;
    }

    // Create the game manager and run the game
    GameManager<char> pyramic_x_o_game(B, players);
    pyramic_x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
}

int game_4()
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
    while (getline(file, word))
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
}

int game_2()
{
    int choice;
    Player<char> *players[2];
    Connect4_Board<char> *B = new Connect4_Board<char>;
    string playerXName, player2Name;

    cout << "Welcome to FCAI Four in a row Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[0] = new Connect4_Player<char>(playerXName, 'X');
        break;
    case 2:
        players[0] = new Connect4_Random_Player<char>('X');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[1] = new Connect4_Player<char>(player2Name, 'O');
        break;
    case 2:
        players[1] = new Connect4_Random_Player<char>('O');
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return 1;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
    return 0;
}

int game_5()
{
    int playerType, numType;
    bool is_odd;
    Player<int> *players[2];
    Numerical_Tic_Tac_Toe_Board<int> *B = new Numerical_Tic_Tac_Toe_Board<int>;
    string playerXName, player2Name;

    cout << "Welcome to FCAI Numerical Tic Tac Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player 1 name: ";
    cin >> playerXName;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> playerType;
    cout << "Choose the number type you want to play with\n"
            "1. Odd\n"
            "2. Even\n";
    cin >> numType;

    vector<int> oddAvailableNums = {1, 3, 5, 7, 9}, evenAvailableNums = {2, 4, 6, 8};

    switch (playerType)
    {
    case 1:
        switch (numType)
        {
        case 1:
            is_odd = true;
            players[0] = new Numerical_Tic_Tac_Toe_Player<int>(playerXName, 0, oddAvailableNums, true);
            break;
        case 2:
            is_odd = false;
            players[0] = new Numerical_Tic_Tac_Toe_Player<int>(playerXName, 0, evenAvailableNums, false);
            break;
        }
        break;
    case 2:
        switch (numType)
        {
        case 1:
            is_odd = true;
            players[0] = new Numerical_Tic_Tac_Toe_Random_Player<int>(0, oddAvailableNums, true);
            break;
        case 2:
            is_odd = false;
            players[0] = new Numerical_Tic_Tac_Toe_Random_Player<int>(0, evenAvailableNums, false);
            break;
        }
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> playerXName;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> playerType;

    is_odd = !is_odd;
    switch (playerType)
    {
    case 1:
        if (is_odd)
            players[1] = new Numerical_Tic_Tac_Toe_Player<int>(playerXName, 0, oddAvailableNums, true);
        else
            players[1] = new Numerical_Tic_Tac_Toe_Player<int>(playerXName, 0, evenAvailableNums, false);
        break;
    case 2:
        if (is_odd)
            players[1] = new Numerical_Tic_Tac_Toe_Random_Player<int>(0, oddAvailableNums, true);
        else
            players[1] = new Numerical_Tic_Tac_Toe_Random_Player<int>(0, evenAvailableNums, false);
        break;
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return 1;
    }

    // Create the game manager and run the game
    GameManager<int> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
    return 0;
}

int game_3()
{
    Player<char> *players[2];
    TicTacToeBoard<char> *board = new TicTacToeBoard<char>();

    string name;
    int choice;

    cout << "Welcome to 5x5 Tic Tac Toe!\n";

    // Player selection
    for (int i = 0; i < 2; i++)
    {
        while (true)
        {
            cout << "Choose Player " << (i + 1) << " type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1)
            {
                cout << "Enter Player " << (i + 1) << " name: ";
                cin >> name;
                players[i] = new TicTacToePlayer<char>(name, (i == 0 ? 'X' : 'O'));
                break;
            }
            else if (choice == 2)
            {
                players[i] = new TicTacToeRandomPlayer<char>((i == 0 ? 'X' : 'O'));
                break;
            }
            else
            {
                cout << "Invalid choice. Please enter 1 or 2.\n";
            }
        }
    }

    int x, y;
    for (int turn = 0; turn < 25; turn++)
    {
        board->display_board();
        Player<char> *current_player = players[board->get_n_moves() % 2]; // %2 so it will be only 0 or 1
        do
        {
            current_player->getmove(x, y);
        } while (!board->update_board(x, y, current_player->getsymbol()));
    }

    board->display_board();

    int x_score = board->count_three_in_row('X');
    int o_score = board->count_three_in_row('O');

    cout << players[0]->getname() << " (X) scored: " << x_score << " three-in-rows.\n";
    cout << players[1]->getname() << " (O) scored: " << o_score << " three-in-rows.\n";

    if (board->is_win())
    {
        Player<char> *winner = x_score > o_score ? players[0] : players[1];
        cout << winner->getname() << " wins!\n";
    }
    else
    {
        cout << "It's a draw!\n";
    }

    delete board;
    delete players[0];
    delete players[1];
    return 0;
}

int game_6()
{
    Player<char> *players[2];
    MisereTicTacToeBoard<char> *board = new MisereTicTacToeBoard<char>();

    string name;
    int choice;

    cout << "Welcome to Misere Tic Tac Toe!\n";

    for (int i = 0; i < 2; i++)
    {
        while (true)
        {
            cout << "Choose Player " << (i + 1) << " type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1)
            {
                cout << "Enter Player " << (i + 1) << " name: ";
                cin >> name;
                players[i] = new MisereTicTacToePlayer<char>(name, (i == 0 ? 'X' : 'O'));
                break;
            }
            else if (choice == 2)
            {
                players[i] = new MisereTicTacToeRandomPlayer<char>((i == 0 ? 'X' : 'O'));
                break;
            }
            else
            {
                cout << "Invalid choice. Please enter 1 or 2.\n";
            }
        }
    }

    // Main game loop
    int turn = 0;
    while (!board->game_is_over())
    {
        board->display_board();
        Player<char> *current_player = players[turn % 2];
        int x, y;
        do
        {
            current_player->getmove(x, y);
        } while (!board->update_board(x, y, current_player->getsymbol()));

        if (board->is_win())
        {
            cout << current_player->getname() << " loses!\n";
            break;
        }

        turn++;
        if (board->is_draw())
        {
            cout << "It's a draw!\n";
            break;
        }
    }

    board->display_board();

    // Cleanup
    delete board;
    delete players[0];
    delete players[1];

    return 0;
}

int game_7()
{
    int choice;
    Player<char> *players[2];
    Board4x4<char> *B = new Board4x4<char>;
    string playerXName, player2Name;

    cout << "Welcome to FCAI Four in a row Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[0] = new Player4x4<char>(playerXName, 'O');
        break;
    case 2:
        players[0] = new RandomPlayer4x4<char>('O');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        players[1] = new Player4x4<char>(player2Name, 'X');
        break;
    case 2:
        players[1] = new RandomPlayer4x4<char>('X');
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return 1;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i)
    {
        delete players[i];
    }
}

int game_8()
{
    Player<char> *players[2];
    Ultimate_Board<char> *board = new Ultimate_Board<char>();

    string name;
    int choice;

    cout << "Welcome to Ultimate Tic Tac Toe!\n";

    for (int i = 0; i < 2; i++)
    {
        while (true)
        {
            cout << "Choose Player " << (i + 1) << " type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1)
            {
                cout << "Enter Player " << (i + 1) << " name: ";
                cin >> name;
                players[i] = new Ultimate_Player<char>(name, (i == 0 ? 'X' : 'O'));
                break;
            }
            else if (choice == 2)
            {
                players[i] = new Ultimate_Random_Player<char>((i == 0 ? 'X' : 'O'));
                break;
            }
            else
            {
                cout << "Invalid choice. Please enter 1 or 2.\n";
            }
        }
    }

    int x, y;
    Player<char> *current_player = nullptr;

    for (int turn = 0; turn < 81; turn++)
    {
        board->display_board();
        current_player = players[board->get_n_moves() % 2];
        do
        {
            current_player->getmove(x, y);
        } while (!board->update_board(x, y, current_player->getsymbol()));

        if (board->game_is_over())
            break;
    }

    board->display_board();

    if (board->is_win())
    {
        cout << "Congratulations! " << current_player->getname() << " is the winner!" << endl;
    }
    else
    {
        cout << "It's a draw!\n";
    }

    delete board;
    delete players[0];
    delete players[1];
    return 0;
}

int main()
{
    cout << "Welcome to our board games program !" << '\n';
    bool exit = false; // To control the loop
    int game_choice;

    while (!exit)
    {
        cout << "\n--- Menu ---\n";
        cout << "Pyramic Tic Tac Toe => 1\n";
        cout << "Connect 4 => 2\n";
        cout << "5x5 Tic Tac Toe => 3\n";
        cout << "Word Tic Tac Toe => 4\n";
        cout << "Numerical Tic Tac Toe => 5\n";
        cout << "Misere Tic Tac Toe => 6\n";
        cout << "4x4 Tic Tac Toe => 7\n";
        cout << "Ultimate Tic Tac Toe => 8\n";
        cout << "Exit => 9\n";
        cout << "Enter your choice: ";
        cin >> game_choice;

        // Input validation
        while (game_choice < 1 || game_choice > 9)
        {
            cout << "Invalid choice! Please enter a number between 1 and 9: ";
            cin >> game_choice;
        }

        switch (game_choice)
        {
        case 1:
            game_1();

            break;

        case 2:
            game_2();

            break;

        case 3:
            game_3();
            break;

        case 4:
            game_4();
            break;

        case 5:
            game_5();
            break;

        case 6:
            game_6();
            break;

        case 7:
            game_7();
            break;

        case 8:
            game_8();
            break;

        case 9:
            cout << "Goodbye :)!\n";
            exit = true;
            break;
        }
    }

    return 0;
}