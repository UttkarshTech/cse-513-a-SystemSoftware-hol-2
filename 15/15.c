/*
============================================================================
Name : 15.c
Author : Uttkarsh Ranjan
Description : Write a simple program to send some data from parent to the child process.
Date: 19th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

void send_message(int write_end, const char *msg) {
    if (write(write_end, msg, strlen(msg) + 1) == -1) {
        perror("write");
        exit(1);
    }
    printf("Parent: Sent message to child: %s\n", msg);
}

void receive_message(int read_end, char *buffer, size_t size) {
    if (read(read_end, buffer, size) == -1) {
        perror("read");
        exit(1);
    }
    printf("Child: Received message from parent: %s\n", buffer);
}

int main() {
    int fds[2];
    pid_t child_pid;
    char message[] = "Hello, child process!";
    char buffer[100];

    if (pipe(fds) == -1) {
        perror("pipe");
        exit(1);
    }

    child_pid = fork();

    if (child_pid < 0) {
        perror("fork");
        exit(1);
    }

    if (child_pid > 0) {
        close(fds[0]);
        send_message(fds[1], message);
        close(fds[1]);
    } else {
        close(fds[1]);
        receive_message(fds[0], buffer, sizeof(buffer));
        close(fds[0]);
    }

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/15$ gcc 15.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/15$ ./a.out
Parent: Sent message to child: Hello, child process!
Child: Received message from parent: Hello, child process!
============================================================================
*/