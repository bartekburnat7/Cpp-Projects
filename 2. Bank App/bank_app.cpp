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

Accounts::Accounts(string username, string password, float balance)
{
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
        
    }
};

int main() {
    cout << R"(
    *******************************************
    *                                         *
    *       BARTEK BANK MANAGEMENT SYSTEM     *
    *                                         *
    *******************************************
    )" << endl;
    
    bank_app BartekBank;
    
    int choice;
    cout << "1. Create Account" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    
    string user_in, pass_in;
    
    switch (choice)
    {
        case 1:
        cin >> user_in;
        cin >> pass_in;
        
        break;
    
    default:
        break;
    }
    
    return 0;
}