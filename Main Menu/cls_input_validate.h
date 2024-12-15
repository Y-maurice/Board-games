//
// Created by Michelle on 10/1/2024.
//
#include <bits/stdc++.h>

using namespace std;

class clsInputValidate {

public:

    static bool IsNumberBetween(int Number, int From, int To) {
        if (Number >= From && Number <= To)
            return true;
        else
            return false;

    }

    static bool IsNumberBetween(double Number, double From, double To) {
        if (Number >= From && Number <= To)
            return true;
        else
            return false;
    }


    static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again\n") {
        short Number;
        while (!(cin >> Number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again\n") {
        int Number;
        while (!(cin >> Number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    static short
    ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again:\n") {
        int Number = ReadShortNumber();

        while (!IsNumberBetween(Number, From, To)) {
            cout << ErrorMessage;
            Number = ReadShortNumber();
        }
        return Number;
    }

    static int
    ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n") {
        int Number = ReadIntNumber();

        while (!IsNumberBetween(Number, From, To)) {
            cout << ErrorMessage;
            Number = ReadIntNumber();
        }
        return Number;
    }

    static double ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n") {
        float Number;
        while (!(cin >> Number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    static double
    ReadFloatNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n") {
        float Number = ReadFloatNumber();

        while (!IsNumberBetween(Number, From, To)) {
            cout << ErrorMessage;
            Number = ReadDblNumber();
        }
        return Number;
    }

    static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n") {
        double Number;
        while (!(cin >> Number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    static double
    ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n") {
        double Number = ReadDblNumber();

        while (!IsNumberBetween(Number, From, To)) {
            cout << ErrorMessage;
            Number = ReadDblNumber();
        }
        return Number;
    }


    static string ReadString() {
        string S1 = "";
        // Usage of std::ws will extract allthe whitespace character
        getline(cin >> ws, S1);
        S1.erase(0, S1.find_first_not_of(" \t\n\r"));
        S1.erase(S1.find_last_not_of(" \t\n\r") + 1);
        return S1;
    }

    static char ReadChar() {
        char c;
        while (!(cin >> c)) {
            cout << "invalid input please enter a character\n";
        }
        return c;
    }

};

bool compTop10List(pair<string,int> p1,pair<string,int> p2){
    return p1.second > p2.second;
}

void AddNewPlayer(vector<pair<string, int>> &Top10List,set<string>& NotTop10List) {
    cout << "Enter player name :";
    string playerName = clsInputValidate::ReadString();
    cout << "Enter player score :";
    int Score = clsInputValidate::ReadIntNumber();
    std::sort(Top10List.begin(), Top10List.end(), compTop10List);
    if(Top10List.size()<10){
        Top10List.emplace_back(playerName, Score);
    }
    else if(Score >= Top10List.back().second && Top10List.size() >=10 ){
        NotTop10List.insert(Top10List.back().first);
        Top10List.pop_back();
        for (int i = 0; i < Top10List.size(); ++i) {
            if(Score>=Top10List[i].second){
                Top10List.insert(Top10List.begin()+i,{playerName,Score});
                break;
            }
        }
    }
    cout<<"Player added successfully :)\n";
}


void PrintTop10PlayersList(vector<pair<string, int>> &Top10List) {
    std::sort(Top10List.begin(), Top10List.end(), compTop10List);
    cout<<"==================================================\n";
    cout<<"\t\t\t Top 10 List\n";
    for (int i = 0; i < Top10List.size(); ++i) {
        cout<<"["<<i+1<<"] "<<"Player name : "<<Top10List[i].first<<" , Score : "<<Top10List[i].second<<endl;
    }
    cout<<"==================================================\n";
}

void SearchForPlayer(vector<pair<string, int>> &Top10List,set<string>& NotTop10List) {
    cout<<"Enter player name : \n";
    string playerName = clsInputValidate::ReadString();
    for (int i = 0; i < Top10List.size(); ++i) {
        if(playerName == Top10List[i].first){
            cout<<"Score : "<<Top10List[i].second<<endl;
            return;
        }
    }
    if (NotTop10List.count(playerName)){
        cout<<"player is not in TOP 10 List\n";
    }else{
        cout<<"Player has not been added \n";
    }
}

