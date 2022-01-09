#include <stdio.h>
#include <iostream>
#include <unistd.h>
// Used for wait() function
#include <sys/types.h>
#include <sys/wait.h>
//
#include <stdlib.h>
#include <cstdlib>
// time
#include <time.h>
using namespace std;

int shutdown_func(){
    printf("Run shutdown function");
    system("shutdown -P +2");
    printf("Return after calling shutdown");
    return 0;
}

class test_time{
public:
    int start_hour;
    int end_hourt;
    int duration;
    int interrupt;
    int sum;

    test_time(int start, int end, int dur, int inter, int s){
        start_hour=start; end_hourt=end; duration=dur; interrupt=inter; sum=s;
    }
};

int test_interval_time() {
    srand(1);
    for (;;) {
        double interval = 10; /* seconds */

        /* start time */
        time_t start = time(NULL);

        /* do something */
        int duration = rand() % 13;
        printf("%2d seconds of work started at %s", duration, ctime(&start));
        sleep(duration);

        /* end time */
        time_t end = time(NULL);

        /* compute remaining time to sleep and sleep */
        double elapsed = difftime(end, start);
        int seconds_to_sleep = (int)(interval - elapsed);
        if (seconds_to_sleep > 0) { /* don't sleep if we're already late */
            sleep(seconds_to_sleep);
        }
    }
    return 0;
}

int main(){
    pid_t pid;
    test_time time = test_time(7, 9, 60, 20, 150);
    cout << time.start_hour << time.duration << endl;
    int a = 3;
    // Fork a child process
    pid = fork();
    pid = fork();
    // pid = fork();

    if (pid < 0){
        fprintf(stderr, "Fork failed");
    } else if (pid == 0){ // child process
        sleep(5);
        printf("test print\n");
        a++;
        cout << "a in chjld = :" << a << endl;
        // test_interval_time();
    } else {
        wait(NULL);
        printf("child complete\n");
        cout << a;
    }
    return 0;
}