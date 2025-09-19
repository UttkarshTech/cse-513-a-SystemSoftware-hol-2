/*
============================================================================
Name : 8b.c
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
#include <signal.h>
#include <unistd.h>

void handle_sigint(int signum) {
    printf("\nReceived SIGINT (signal %d). Exiting safely.\n", signum);
    _exit(0);
}

int main() {
    signal(SIGINT, handle_sigint);

    while (1) {
        printf("Program running... Press Ctrl+C to stop.\n");
        sleep(1);
    }

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/8$ gcc 8b.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/8$ ./a.out
Program running... Press Ctrl+C to stop.
Program running... Press Ctrl+C to stop.
Program running... Press Ctrl+C to stop.
^C
Received SIGINT (signal 2). Exiting safely.
============================================================================
*/