/*
============================================================================
Name : 10c.c
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

void handle_sigfpe(int sig, siginfo_t *info, void *context) {
    printf("SIGFPE caught! Signal = %d, reason code = %d\n", sig, info->si_code);
    _exit(1);
}

void setup_fpe_handler() {
    struct sigaction action;
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = handle_sigfpe;
    sigemptyset(&action.sa_mask);

    if (sigaction(SIGFPE, &action, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

int main() {
    setup_fpe_handler();
    int denom = 0;
    int result = 5 / denom;
    printf("%d\n", result);
    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/10$ gcc 10c.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/10$ ./a.out
SIGFPE caught! Signal = 8, reason code = 1
============================================================================
*/