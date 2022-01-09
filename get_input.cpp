/*
https://stackoverflow.com/questions/39539400/execvp-not-working-in-my-shell
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_CHARACTERS 512
#define HISTORY_SIZE 10

int commandSplit(char *c, char *a[], int t[]) {

    int count = 0;
    int total = 0;
    char *temp[MAX_CHARACTERS];
    char *readCommands = strtok(c, ";");
    while(readCommands != NULL) {
        printf("Reading full command: %s\n", readCommands);
        temp[count] = readCommands;
        count++;
        readCommands = strtok(NULL, ";");
    }
    printf("Done reading full commands\n");
    for(int i = 0; i  < count; i++) {
        char *read = strtok(temp[i], " ");
        int track = 0;
        while(read != NULL) {
            printf("Reading individual command: %s\n", read);
            a[total] = read;
            track++;
            total++;
            read = strtok(NULL, " ");
        }
        t[i] = track;
    }

    return count;
}

int main() {

    int exitProgram = 0;
    char *args[MAX_CHARACTERS];

    while(!exitProgram) {

    char *commands = (char *)(malloc(MAX_CHARACTERS*sizeof(char)));
    int tracker[MAX_CHARACTERS];
    int numOfCommands = 0;
    printf("tinyshell> ");
    fgets(commands, MAX_CHARACTERS, stdin);

    if(strlen(commands) == 0) continue;

    numOfCommands = commandSplit(commands, args, tracker);
    printf("There are %i commands!\n", numOfCommands);

    if(strcmp(args[0], "exit") == 0) {
        printf("Exiting\n");
        exitProgram = 1;
        continue;
    }

    int l = 0;
    for(int i = 0; i < numOfCommands; i++) {
        int status;
        char *holder[tracker[i]+1];
        for(int j = 0; j < tracker[i]; j++) {
            holder[j] = args[l];
            printf("Assiging holder:%s\n", holder[j]);
            l++;
        }
        holder[tracker[i]] = NULL;
        printf("What is holder? \n");
        for(int o = 0; o < tracker[i]; o++) printf("%s", holder[o]);
        pid_t p = fork();
        pid_t waiting;
        if(p == 0) {
            printf("I am in child process\n");
            execvp(holder[0], holder);

            fprintf(stderr, "Child process could not execvp!\n");
            exit(1);
        }
        else {
            if(p < 0) {
                fprintf(stderr, "Fork FAILED!\n");
            }
            else {
                waiting = wait(&status);
                printf("Child %d, status %d\n", waiting, status);
            }
        }
        for(int i = 0; i < numOfCommands; i++) {
            args[i] = NULL;
        }
    }

}   

    return 0;

}