/*
============================================================================
Name : 3.c
Author : Uttkarsh Ranjan
Description : Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 19th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main() {
    struct rlimit r;

    if (getrlimit(RLIMIT_NOFILE, &r) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    printf("Before update:\n");
    printf("Soft limit = %ld\n", (long)r.rlim_cur);
    printf("Hard limit = %ld\n", (long)r.rlim_max);

    r.rlim_cur = 4096;

    if (setrlimit(RLIMIT_NOFILE, &r) == -1) {
        perror("setrlimit");
        exit(EXIT_FAILURE);
    }

    if (getrlimit(RLIMIT_NOFILE, &r) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    printf("\nAfter update:\n");
    printf("Soft limit = %ld\n", (long)r.rlim_cur);
    printf("Hard limit = %ld\n", (long)r.rlim_max);

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/3$ gcc 3.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/3$ ./a.out
Before update:
Soft limit = 1024
Hard limit = 1048576

After update:
Soft limit = 4096
Hard limit = 1048576
============================================================================
*/