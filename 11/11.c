/*
============================================================================
Name : 11.c
Author : Uttkarsh Ranjan
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal -
use sigaction system call.
Date: 19th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void set_signal_ignore(int signum) {
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(signum, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

void set_signal_default(int signum) {
    struct sigaction sa;
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(signum, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

int main() {
    printf("Step 1: SIGINT is ignored for 5 seconds.\n");
    set_signal_ignore(SIGINT);
    sleep(5);

    printf("Step 2: SIGINT reset to default action.\n");
    set_signal_default(SIGINT);

    while (1) {
        printf("Running...\n");
        sleep(1);
    }

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/11$ gcc 11.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/11$ ./a.out
Step 1: SIGINT is ignored for 5 seconds.
^C^CStep 2: SIGINT reset to default action.
Running...
Running...
^C
============================================================================
*/