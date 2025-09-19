/*
============================================================================
Name : 1b.c
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

void virtual_timer_handler(int sig) {
    printf("ITIMER_VIRTUAL expired! Signal = %d\n", sig);
}

void configure_virtual_timer(int sec, int usec) {
    struct itimerval timer;
    timer.it_interval.tv_sec = sec;
    timer.it_interval.tv_usec = usec;
    timer.it_value.tv_sec = sec;
    timer.it_value.tv_usec = usec;

    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }
}

void busy_loop() {
    for (volatile int i = 0; ; i++);
}

int main() {
    signal(SIGVTALRM, virtual_timer_handler);
    configure_virtual_timer(10, 10);
    busy_loop();
    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/1$ gcc 1b.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/1$ ./a.out
ITIMER_VIRTUAL expired! Signal = 26
ITIMER_VIRTUAL expired! Signal = 26
ITIMER_VIRTUAL expired! Signal = 26
ITIMER_VIRTUAL expired! Signal = 26
ITIMER_VIRTUAL expired! Signal = 26
^C
============================================================================
*/