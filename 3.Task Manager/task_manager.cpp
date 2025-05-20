/*
* Project: TaskMaster++
* Purpose: Learn intermediate C++ by simulating a task manager system.
* Author: Bartek
* Date: 2025-05-17
* 
* C++ Concepts Practiced:
* - Classes and Encapsulation
* - Vectors and Data Structures
* - Enums
* - chrono (time/date)
* - File I/O (save/load tasks)
* - Operator Overloading (<<, >>)
* - Smart Pointers (shared_ptr)
* - Sorting with Lambdas
* 
* Goals:
* 1. Manage a list of tasks with title, description, deadline, and priority.
* 2. Allow user to create, delete, edit, view, and sort tasks.
* 3. Support saving and loading tasks from a file.
* 4. Use clean OOP design with separate class definitions and logic.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "SHA256.h"

using namespace std;

/* Priorities for the TaskData */
#define HIGH 3
#define MED 2
#define LOW 1
/* Data For the Task Mngr*/
namespace TaskData
{
    class task{
        private:
            unsigned int ID;
            struct tm date;
        public:
            void create_task(int yr, int m, int day, int hr, int min){
                date.tm_year = yr - 1900;
                date.tm_mon = m - 1;
                date.tm_mday = day;
                date.tm_hour = hr;
                date.tm_min = min;
                date.tm_isdst = -1;
                ID = 1;
            }
            tm* get_date(){
                return &date;
            };
     };

    class user{
        protected:
            struct user_data{
                unsigned int ID;
                string name;
                string username;
                string password;
            };

        public:
            user_data create_user(string name_in, string username_in, string password_in){
                user_data user_data_object;
                SHA256 sha;
                sha.update(password_in);
                array<uint8_t, 32> hashed_password = sha.digest();
                user_data_object.ID = 1;// remeber to change it to auto increment
                user_data_object.name = name_in;
                user_data_object.username = username_in;
                user_data_object.password = sha.toString(hashed_password);
                return user_data_object;
            };
    };    
}
/* Task Manager */

class task_manager
{
    protected:
        ofstream my_database;
        string login_id;
    public:
        int load_database(){
            my_database.open("my_database.csv", ios::app);
            if (!my_database.is_open()) {
                cerr << "Error opening file!" << endl;
                return 1;
            };
            return 0;
        };
        void create_user_main(){
            string name, username, password;
            cin >> name;
            cin >> username;
            cin >> password;
            TaskData::user user_instance;
            auto user_obj = user_instance.create_user(name,username,password);
            if (!load_database()){
                my_database.seekp(0, ios::end);
                my_database << to_string(user_obj.ID) + "," +user_obj.name + "," +user_obj.username + "," +user_obj.password + "\n";
                cout << "User created successfully!" << endl;
            }

        }
};
// Run Task Manager

int main(){
    task_manager mngr;
    mngr.create_user_main();
    return 0;
};