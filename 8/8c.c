/*
============================================================================
Name : 8c.c
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
#include <stdlib.h>

void handle_sigfpe(int signum) {
    printf("Signal SIGFPE caught (signal %d). Exiting immediately.\n", signum);
    exit(1);
}

int main() {
    signal(SIGFPE, handle_sigfpe);

    int numerator = 10;
    int denominator = 0;
    int result = numerator / denominator;  // triggers SIGFPE
    printf("%d\n", result);

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/8$ gcc 8c.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/8$ ./a.out
Signal SIGFPE caught (signal 8). Exiting immediately.
============================================================================
*/
