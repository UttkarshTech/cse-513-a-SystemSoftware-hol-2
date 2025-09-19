/*
============================================================================
Name : 2.c
Author : Uttkarsh Ranjan
Description : Write a program to print the system resource limits. Use getrlimit system call.
Date: 19th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void show_limit(int res, const char *label) {
    struct rlimit lim;
    if (getrlimit(res, &lim) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    printf("%-20s: ", label);

    if (lim.rlim_cur == RLIM_INFINITY)
        printf("Current = unlimited, ");
    else
        printf("Current = %ld, ", (long)lim.rlim_cur);

    if (lim.rlim_max == RLIM_INFINITY)
        printf("Max = unlimited\n");
    else
        printf("Max = %ld\n", (long)lim.rlim_max);
}

int main() {
    printf("System Resource Limits:\n\n");

    show_limit(RLIMIT_CPU, "CPU time (seconds)");
    show_limit(RLIMIT_FSIZE, "File size (bytes)");
    show_limit(RLIMIT_DATA, "Data segment size");
    show_limit(RLIMIT_STACK, "Stack size");
    show_limit(RLIMIT_CORE, "Core file size");
    show_limit(RLIMIT_RSS, "Resident set size");
    show_limit(RLIMIT_NPROC, "Number of processes");
    show_limit(RLIMIT_NOFILE, "Open files");
    show_limit(RLIMIT_MEMLOCK, "Locked memory");
    show_limit(RLIMIT_AS, "Address space");
    show_limit(RLIMIT_LOCKS, "File locks");
    show_limit(RLIMIT_SIGPENDING, "Pending signals");
    show_limit(RLIMIT_MSGQUEUE, "POSIX message queues");
    show_limit(RLIMIT_NICE, "Nice priority");
    show_limit(RLIMIT_RTPRIO, "Realtime priority");
    show_limit(RLIMIT_RTTIME, "Realtime timeout");

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/2$ gcc 2.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/2$ ./a.out
System Resource Limits:

CPU time (seconds)  : Current = unlimited, Max = unlimited
File size (bytes)   : Current = unlimited, Max = unlimited
Data segment size   : Current = unlimited, Max = unlimited
Stack size          : Current = 8388608, Max = unlimited
Core file size      : Current = 0, Max = unlimited
Resident set size   : Current = unlimited, Max = unlimited
Number of processes : Current = 31450, Max = 31450
Open files          : Current = 1024, Max = 1048576
Locked memory       : Current = 1040953344, Max = 1040953344
Address space       : Current = unlimited, Max = unlimited
File locks          : Current = unlimited, Max = unlimited
Pending signals     : Current = 31450, Max = 31450
POSIX message queues: Current = 819200, Max = 819200
Nice priority       : Current = 0, Max = 0
Realtime priority   : Current = 0, Max = 0
Realtime timeout    : Current = unlimited, Max = unlimited
============================================================================
*/