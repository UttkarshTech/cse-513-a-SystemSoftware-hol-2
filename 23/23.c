/*
============================================================================
Name : 23.c
Author : Uttkarsh Ranjan
Description : Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
Date: 22nd September 2025
============================================================================
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void show_open_max() {
    long val = sysconf(_SC_OPEN_MAX);
    if (val == -1) {
        perror("sysconf(_SC_OPEN_MAX)");
    } else {
        printf("Maximum number of open files per process: %ld\n", val);
    }
}

void show_pipe_size() {
    int fds[2];
    if (pipe(fds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int size = fcntl(fds[0], F_GETPIPE_SZ);
    if (size == -1) {
        perror("fcntl(F_GETPIPE_SZ)");
    } else {
        printf("Default pipe (circular buffer) size: %d bytes\n", size);
    }

    close(fds[0]);
    close(fds[1]);
}

int main() {
    show_open_max();
    show_pipe_size();
    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/23$ gcc 23.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/23$ ./a.out
Maximum number of open files per process: 1024
Default pipe (circular buffer) size: 65536 bytes
============================================================================
*/