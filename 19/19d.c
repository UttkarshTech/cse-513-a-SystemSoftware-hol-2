/*
============================================================================
Name : 19d.c
Author : Uttkarsh Ranjan
Description : Create a FIFO file by
                a. mknod command
                b. mkfifo command
                c. use strace command to find out, which command (mknod or mkfifo) is better.
                c. mknod system call
                d. mkfifo library function
Date: 20th September 2025
============================================================================
*/

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main() {
    const char *fname = "19_lib";

    if (mkfifo(fname, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    printf("FIFO created using mkfifo library function: %s\n", fname);
    return 0;
}