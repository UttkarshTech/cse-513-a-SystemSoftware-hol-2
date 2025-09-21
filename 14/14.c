/*
============================================================================
Name : 14.c
Author : Uttkarsh Ranjan
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on
the monitor.
Date: 19th September 2025
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void write_to_pipe(int write_end, const char *msg) {
    if (write(write_end, msg, strlen(msg) + 1) == -1) {
        perror("write");
        exit(1);
    }
    printf("Written to pipe: %s\n", msg);
}

void read_from_pipe(int read_end, char *buffer, size_t size) {
    if (read(read_end, buffer, size) == -1) {
        perror("read");
        exit(1);
    }
    printf("Read from pipe: %s\n", buffer);
}

int main() {
    int fds[2];
    char message[] = "Hello from pipe!";
    char buffer[100];

    if (pipe(fds) == -1) {
        perror("pipe");
        exit(1);
    }

    write_to_pipe(fds[1], message);
    read_from_pipe(fds[0], buffer, sizeof(buffer));

    close(fds[0]);
    close(fds[1]);

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/14$ gccuttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/14$ ./a.out
Written to pipe: Hello from pipe!
Read from pipe: Hello from pipe!
============================================================================
*/