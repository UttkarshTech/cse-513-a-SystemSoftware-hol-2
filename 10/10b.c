/*
============================================================================
Name : 10b.c
Author : Uttkarsh Ranjan
Description : Write a separate program using sigaction system call to catch the following signals.
            a. SIGSEGV
            b. SIGINT
            c. SIGFPE
Date: 19th September 2025
============================================================================
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig, siginfo_t *info, void *context) {
    printf("\nSIGINT caught! Signal = %d. Exiting safely.\n", sig);
    _exit(0);
}

void setup_sigint_handler() {
    struct sigaction action;
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = handle_sigint;
    sigemptyset(&action.sa_mask);

    if (sigaction(SIGINT, &action, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

int main() {
    setup_sigint_handler();
    while (1) {
        printf("Running... Press Ctrl+C to stop.\n");
        sleep(1);
    }
    return 0;
}

/*
============================================================================
ttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/10$ gcc 10b.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/10$ ./a.out
Running... Press Ctrl+C to stop.
Running... Press Ctrl+C to stop.
Running... Press Ctrl+C to stop.
^C
SIGINT caught! Signal = 2. Exiting safely.
============================================================================
*/
