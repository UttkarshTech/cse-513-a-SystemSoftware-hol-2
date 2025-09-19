/*
============================================================================
Name : 1c.c
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

void sig_handler(int s) {
    printf("ITIMER_PROF expired! Signal = %d\n", s);
}

void start_prof_timer() {
    struct itimerval t;
    t.it_interval.tv_sec = 10;
    t.it_interval.tv_usec = 10;
    t.it_value.tv_sec = 10;
    t.it_value.tv_usec = 10;

    if (setitimer(ITIMER_PROF, &t, NULL) == -1) {
        perror("setitimer error");
        exit(EXIT_FAILURE);
    }
}

int main() {
    if (signal(SIGPROF, sig_handler) == SIG_ERR) {
        perror("signal error");
        exit(EXIT_FAILURE);
    }

    start_prof_timer();

    while (1) {
        for (volatile int k = 0; k < 1000000; k++);
    }

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/1$ gcc 1c.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/1$ ./a.out
ITIMER_PROF expired! Signal = 27
ITIMER_PROF expired! Signal = 27
ITIMER_PROF expired! Signal = 27
^C
============================================================================
*/