/*
============================================================================
Name : 1a.c
Author : Uttkarsh Ranjan
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second
            a. ITIMER_REAL
            b. ITIMER_VIRTUAL
            c. ITIMER_PROF
Date: 19th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void handler(int sig) {
    printf("ITIMER_REAL expired! Signal = %d\n", sig);
}

int main() {
    struct itimerval timer;
    signal(SIGALRM, handler);

    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;
    
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    while (1) {
        pause();
    }

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/1$ gcc 1a.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/1$ ./a.out
ITIMER_REAL expired! Signal = 14
ITIMER_REAL expired! Signal = 14
ITIMER_REAL expired! Signal = 14
ITIMER_REAL expired! Signal = 14
ITIMER_REAL expired! Signal = 14
ITIMER_REAL expired! Signal = 14
ITIMER_REAL expired! Signal = 14
ITIMER_REAL expired! Signal = 14
ITIMER_REAL expired! Signal = 14
ITIMER_REAL expired! Signal = 14
^C
============================================================================
*/