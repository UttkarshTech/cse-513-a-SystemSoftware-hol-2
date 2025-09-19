/*
============================================================================
Name : 8e.c
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

void handle_alarm(int sig) {
    printf("SIGALRM received (signal %d) from setitimer!\n", sig);
}

int main() {
    signal(SIGALRM, handle_alarm);

    struct itimerval one_shot_timer = {{1, 0}, {2, 0}};
    setitimer(ITIMER_REAL, &one_shot_timer, NULL);

    pause();
    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/8$ gcc 8e.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/8$ ./a.out
SIGALRM received (signal 14) from setitimer!
============================================================================
*/
