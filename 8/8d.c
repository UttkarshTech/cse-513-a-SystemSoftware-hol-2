/*
============================================================================
Name : 8d.c
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
#include <unistd.h>

void handle_alarm(int signal_num) {
    printf("Received SIGALRM (signal %d) from alarm()\n", signal_num);
}

int main() {
    signal(SIGALRM, handle_alarm);

    printf("Alarm set for 3 seconds...\n");
    alarm(3);

    pause();
    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/8$ gcc 8d.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/8$ ./a.out
Alarm set for 3 seconds...
Received SIGALRM (signal 14) from alarm()
============================================================================
*/
