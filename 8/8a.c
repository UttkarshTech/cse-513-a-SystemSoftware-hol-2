/*
============================================================================
Name : 8a.c
Author : Uttkarsh Ranjan
Description : Write a separate program using signal system call to catch the following signals.
            a. SIGSEGV
            b. SIGINT
            c. SIGFPE
            d. SIGALRM (use alarm system call)
            e. SIGALRM (use setitimer system call)
            f. SIGVTALRM (use setitimer system call)
            g. SIGPROF (use setitimer system call)
Date: 19th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigsegv_handler(int sig) {
    printf("Caught SIGSEGV (signal %d)!\n", sig);
    exit(1);
}

int main() {
    signal(SIGSEGV, sigsegv_handler);
    int *ptr = NULL;
    *ptr = 42;

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/8$ gcc 8a.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/8$ ./a.out
Caught SIGSEGV (signal 11)!
============================================================================
*/