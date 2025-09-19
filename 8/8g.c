/*
============================================================================
Name : 8g.c
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
#include <sys/time.h>
#include <unistd.h>

void profiling_timer_handler(int sig) {
    printf("SIGPROF received (signal %d)!\n", sig);
}

int main() {
    signal(SIGPROF, profiling_timer_handler);

    struct itimerval prof_timer = {{1, 0}, {2, 0}};
    setitimer(ITIMER_PROF, &prof_timer, NULL);

    for (volatile long counter = 0; ; counter++);

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/8$ gcc 8g.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/8$ ./a.out
SIGPROF received (signal 27)!
SIGPROF received (signal 27)!
SIGPROF received (signal 27)!
SIGPROF received (signal 27)!
SIGPROF received (signal 27)!
SIGPROF received (signal 27)!
^C
============================================================================
*/
