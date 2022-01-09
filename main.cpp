#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
// Used for wait() function
#include <sys/types.h>
#include <sys/wait.h>
//
#include <stdlib.h>
#include <cstdlib>
// time
#include <time.h>
#include <vector>
using namespace std;
// self-defined
#include "defined_time.h"

vector<string> read_accounts(string);
int incorrect_pass_count = 0;

// Global variables
vector<string> adults_list = read_accounts("accounts/adults.txt");
vector<string> childs_list = read_accounts("accounts/childs.txt");


vector<string> read_accounts(string filename){
    ifstream file(filename);
    int size;
    file >> size;
    vector<string> result;

    for (int i = 0; i < size; i++){
        string temp;
        file >> temp;
        result.push_back(temp);
    }

    file.close();
    return result;
}



int login_form(){
    /*
    Return:
        1: is a adult account
        2: is a child account
        0: not account
    */
    string pw_input;
    cout << "\nPassword input: ";
    fflush(stdin);
    getline(cin, pw_input);
    
    for (int i = 0; i < adults_list.size(); i++)
        if (pw_input.compare(adults_list[i]) == 0)
            return 1;
    for (int i = 0; i < childs_list.size(); i++)
        if (pw_input.compare(childs_list[i]) == 0)
            return 2;
    return 0;
}

bool isPermission(){

    return false;
}

void start_point(bool start=true){
    int login_bool = login_form();

    if (login_bool == 1){
        // this is adult password
        if (start == false)
            /* This is when user re-enter correct password after inside logged in childrent context
            */
            system("shutdown -c");
        

        while(1){
            sleep(30);
            start_point();
        }
    } else if (login_bool == 2){
        // This is childrent password

        // Check admitted time to use
        // Code 
        if (isPermission()){
            // If child can use computer in this time
            // Notify how many remain minutes is permitted to using,
            // and the time when children can re-turn on computer
            //Code ....


            // Create 3 concurrent processes
            pid_t process_list[3];
            for (int i = 0; i < 3; i++){
                pid_t pid_item = fork();

                if (pid_item < 0){
                    fprintf(stderr, "Fork failed");
                } else if (pid_item == 0){
                    // this is child process


                    exit(1);
                } else {
                    // This is parent calling
                    process_list[i] = pid_item;
                }
            }

            for (int i = 0; i < 3; i++){
                int status;
                waitpid(process_list[i], &status, 0);
                
            }

        } else {
            // Not permit to use computer in this time.
            cout << "This time is not permitted to use computer. ";
            cout << "Please wait to ...." << endl;
            // Create 2 processes
            // - Shutdown after 1 minute
            // - return back to login form
            pid_t proc_id = fork();

            if (proc_id < 0){
                fprintf(stderr, "Fork failed");
            } else if (proc_id == 0){
                // 1 process will schedule shutdown time
                system("shutdown -P +5");
                exit(1); // stop this process in here.
            } else {
                // This is parent calling
                // This will lead user to login form, if user re-enter correct password
                // program cancel shutdown command previously
                
                wait(NULL);
                cout << "Call python file" << endl;
                start_point(false);
            }
        }
    } else {
        // When user enter incorrect password, not child or parents
        incorrect_pass_count += 1;
        cout << "You have entered incorrect password " << incorrect_pass_count << " times" << endl;
        
        if (incorrect_pass_count >= 3){
        // Lock this computer in 10 minutes
            const char* lock_command = "gnome-session-quit";
            system(lock_command);
        // shutdown now
            system("shutdown -P +30");
        }
        else
            start_point();
    }
}

void read_time_file(string filename){
    ofstream file("times.txt");


    file.close();
}

int main(){
    // pid_t main_process;

    // main_process = fork();

    // if (main_process < 0){
    //     fprintf(stderr, "Fork failed");
    // } else if (main_process == 0){
    //     // This is a child process
    //     cout << "child" << endl;
    //     // system("shutdown -P +5");
    //     sleep(5);
    //     cout << "exit" << endl;
    //     exit(1);
    //     cout << "exiteddd" << endl;
    // } else{
    //     // This is a main process
    //     // wait(NULL);
    //     cout << "parent" << endl;
    //     system("shutdown -c");
    //     sleep(10);
    // }

    start_point();

    // const char* time_details = "09:37";
    // struct tm tm;
    // strptime(time_details, "%H:%M", &tm);
    // time_t t = mktime(&tm);

    // cout << ctime(&t) << endl;
    // // ctime() is used to convert time_t to string format.
    // time_t start = time(NULL);
    // cout << ctime(&start) << endl;
    // double elapsed = difftime(start, t);
    
    return 0;
}