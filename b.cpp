// #define _GNU_SOURCE
#include <iostream>
using namespace std;
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <signal.h>
#define FIBER_STACK 8192

void * stack;
int do_something(void* arg){
    int a = 0;
    while (a<10){
        printf("pid : %d, a = %d\n", getpid(), a++);
    }
    exit(1);
}
int main() {
    void * stack;
    stack = malloc(FIBER_STACK);
    if(!stack) {
        printf("The stack failed\n");
        exit(0);
    }

    int a = 0;
    if (a == 0)
        clone(&do_something, (char *)stack + FIBER_STACK, CLONE_VM, 0);
    while (a<10){
        printf("pid : %d, a = %d\n", getpid(), a++);
    }

    free(stack);
    exit(1);
}