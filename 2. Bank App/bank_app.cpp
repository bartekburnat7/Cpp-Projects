/*
* Project: Bank Account Management System
* Concepts: Classes, Encapsulation, Member Functions, Vectors (optional)
* Goal: Build a functional OOP bank system with accounts, deposits, withdrawals, and extendable features
* Status: Initial version created on 2025-05-16
* Purpose: Practice OOP in C++ by modeling bank accounts with basic operations
*/

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;

class Accounts
{
private:
    string username;
    string password;
    float balance;    
public:
    Accounts(string username, string password, float balance = 0.00);
    float getBalance(){
        return balance;
    };
    bool addBalance(float bal){
        balance += bal;
        cout << "Your current balance: $" << balance << endl;
        return 1;
    };
    pair<string,string> getDetail(){
        return make_pair(username,password);
    };
};

Accounts::Accounts(string username_in, string password_in, float balance_in)
{
    username = username_in;
    password = password_in;
    balance = balance_in;
}

class bank_app
{
private:
    vector<Accounts> accounts;
    vector<pair<string,shared_ptr<Accounts>>> sessions;
public:
    bank_app(){accounts.reserve(10);}
    bool createUser(string username, string password){
        accounts.emplace_back(username,password);
        return true;
    };
    string login(string user, string pass){
        for (auto i:accounts){
            if (user == i.getDetail().first && pass == i.getDetail().second){
                srand(time(nullptr));
                int rnum = rand() % 1000 + 1;
                string session_id = to_string(rnum);
                sessions.push_back(make_pair(session_id, make_shared<Accounts>(i)));
                cout << "Welcome!" << endl;
                return session_id;
            };
        };
        cout << "not found :(";
        return "not found";
    };
    float addMoney(float money_add, string session_id){
        for (auto i:sessions){
            if (i.first == session_id){
                i.second -> addBalance(money_add);
                return money_add;
            };
        };
        return 0.0;    
    };
    float viewBalance(string session_id){
        for (auto i: sessions){
            if(i.first == session_id){
                float current_balance = i.second -> getBalance();
                cout << endl;
                return current_balance;
            }
        };
        return -1;
    };
    float sendMoney(string session_id, string user_to, float amount){
        bool from = false ,to = false;
        for (auto i: sessions){
            if(i.first == session_id){
                i.second -> addBalance(-amount);
                break;
            };
        };
        for (auto& i:accounts){
            if (user_to == i.getDetail().first){
                i.addBalance(amount);
            };
        };
        return 0;
    };
};

int main() {
    int choice;
    float money_in, amount;
    string user_in, pass_in, message, my_session, account_statement, reciver;
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
        if (!my_session.empty()){
            cout << account_statement << endl;
        }

        if (!message.empty()){
            cout << message << endl;
        }
        
        
        cout << "1. Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Add Money" << endl;
        cout << "4. send money" << endl;
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
                message = user_in + " created!";
                system("cls");
                break;
            case 2:
                cout << "Username: ";
                cin >> user_in;
                cout << "Password: ";
                cin >> pass_in;
                my_session = BartekBank.login(user_in,pass_in);
                message = "logged in as " + user_in;
                account_statement = "Current Account Balance: $" + to_string(BartekBank.viewBalance(my_session));
                system("cls");
                break;
            case 3:
                {
                    cout << "how much money you want to add: ";
                    cin >> money_in;
                    float money_added = BartekBank.addMoney(money_in, my_session);
                    message = to_string(money_added)+" has been added to your account.";
                    account_statement = "Current Account Balance: $" + to_string(BartekBank.viewBalance(my_session));
                    system("cls");
                    break;
                }
            case 4:
                cout << "Enter reciver username: ";
                cin >> reciver;
                cout << "Enter Amount: ";
                cin >> amount;
                BartekBank.sendMoney(my_session,reciver,amount);
                message = "Money has been sent";
                account_statement = "Current Account Balance: $" + to_string(BartekBank.viewBalance(my_session));
                system("cls");
                break;
        };
    };
    return 0;
};