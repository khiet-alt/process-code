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


int main(){
    pid_t pids[5];
    for (int i  = 0 ; i < 5 ; i++) { // Start i at 0, not at 1
        pid_t pid = fork();
        if (pid < 0) {
            break;
        } else if (pid > 0) {
            pids[i] = pid;
        } else {
            char cmd[1024];
            sprintf(cmd, "%i", i+1);
            sleep(5);
            // system(cmd);
            // exit(1);
        }
    }
    for (int i  = 0 ; i < 5 ; i++) {
        int status;
        // waitpid(pids[i], &status, 0);
        printf("Command %i has completed successfully by PID=%d\n", i+1, pids[i]);
    }
    cout << "\n";
    cout << "times\n";

}

// // This only check there is a clicked button, not specially which button

// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/time.h>
// #include <sys/types.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <termios.h>

// int main()
// {
//     struct termios oldSettings, newSettings;

//     tcgetattr( fileno( stdin ), &oldSettings );
//     newSettings = oldSettings;
//     newSettings.c_lflag &= (~ICANON & ~ECHO);
//     tcsetattr( fileno( stdin ), TCSANOW, &newSettings );    

//     while ( 1 )
//     {
//         fd_set set;
//         struct timeval tv;

//         tv.tv_sec = 10;
//         tv.tv_usec = 0;

//         FD_ZERO( &set );
//         FD_SET( fileno( stdin ), &set );

//         int res = select( fileno( stdin )+1, &set, NULL, NULL, &tv );

//         if( res > 0 )
//         {
//             char c;
//             printf( "Input available\n" );
//             read( fileno( stdin ), &c, 1 );
//         }
//         else if( res < 0 )
//         {
//             perror( "select error" );
//             break;
//         }
//         else
//         {
//             printf( "Select timeout\n" );
//         }
//     }

//     tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <xdo.h>
#include <unistd.h>

int main() {
    xdo_t * x = xdo_new(":0.0");

    while(1) {
        printf("simulating Shift_L keypress\n");
        xdo_keysequence(x, CURRENTWINDOW, "Shift_L", 0);
        sleep(5);
    }

        return 0; 
}

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>