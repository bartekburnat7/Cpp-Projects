/*
* Project: Bank Account Management System
* Concepts: Classes, Encapsulation, Member Functions, Vectors (optional)
* Goal: Build a functional OOP bank system with accounts, deposits, withdrawals, and extendable features
* Status: Initial version created on 2025-05-16
* Purpose: Practice OOP in C++ by modeling bank accounts with basic operations
*/

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <stdlib.h>
using namespace std;

class Accounts
{
private:
    string username;
    string password;
    float balance;    
public:
    Accounts(string username, string password, float balance = 0.00);
    void getBalance(){
        cout << "Current Balance - $" << balance << endl;
    };
    pair<string,string> getDetail(){
        return make_pair(username,password);
    };
};

Accounts::Accounts(string username_in, string password_in, float balance_in)
{
    username = username_in;
    password = password_in;
    cout << username << " - Acount has been created!" << endl;
}

class bank_app
{
private:
    vector<Accounts> accounts;
public:
    bool createUser(string username, string password){
        accounts.emplace_back(username,password);
        return true;
    };
    bool login(string user, string pass){
        for (auto i:accounts){
            if (user == i.getDetail().first && pass == i.getDetail().first){
                cout << "Welcome!" << endl;
                return true;
            }
        }
        cout << "not found :(";
        return false;
    }
    void getusers(){
        for (auto i:accounts){
            cout << i.getDetail().first << endl;
        }
    }
};

int main() {
    int choice;
    string user_in, pass_in;
    bank_app BartekBank;
    system("cls");
    while (true)
    {
        
        cout << R"(
*******************************************
*                                         *
*       BARTEK BANK MANAGEMENT SYSTEM     *
*                                         *
*******************************************
        )" << endl;
        
        
        cout << "1. Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        

        switch (choice)
        {
            case 1:
                cout << "New Username: " << flush;
                cin >> user_in;
                cout << "Create Password: ";
                cin >> pass_in;
                BartekBank.createUser(user_in,pass_in);
                BartekBank.getusers();
                break;
            case 2:
                cout << "Username: ";
                cin >> user_in;
                cout << "Password: ";
                cin >> pass_in;
                BartekBank.login(user_in,pass_in);
                break;
        
        default:
            break;
        }
    };
    return 0;
}