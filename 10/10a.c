/*
============================================================================
Name : 10a.c
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

void handle_sigsegv(int sig, siginfo_t *info, void *context) {
    printf("Segmentation fault caught! Signal = %d, Faulty address = %p\n", sig, info->si_addr);
    _exit(1);
}

void setup_sigsegv_handler() {
    struct sigaction action;
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = handle_sigsegv;
    sigemptyset(&action.sa_mask);

    if (sigaction(SIGSEGV, &action, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

int main() {
    setup_sigsegv_handler();
    int arr[5];
    int *p = arr + 10;
    *p = 42;
    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/10$ gcc 10a.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/10$ ./a.out
Segmentation fault caught! Signal = 11, Faulty address = 0x70e50000002a
============================================================================
*/
