/*
============================================================================
Name : 16.c
Author : Uttkarsh Ranjan
Description : Write a program to send and receive data from parent to child vice versa. Use two way
communication.
Date: 20th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

void send_msg(int fd, const char *msg, const char *who) {
    if (write(fd, msg, strlen(msg) + 1) == -1) {
        perror("write");
        exit(1);
    }
    printf("%s: Sent message: %s\n", who, msg);
}

void recv_msg(int fd, char *buffer, size_t size, const char *who) {
    if (read(fd, buffer, size) == -1) {
        perror("read");
        exit(1);
    }
    printf("%s: Received message: %s\n", who, buffer);
}

int main() {
    int parent_to_child[2], child_to_parent[2];
    pid_t pid;
    char parent_msg[] = "Hello, child!";
    char child_msg[] = "Hello, parent!";
    char buffer[100];

    if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {
        close(parent_to_child[0]);
        close(child_to_parent[1]);

        send_msg(parent_to_child[1], parent_msg, "Parent");
        recv_msg(child_to_parent[0], buffer, sizeof(buffer), "Parent");

        close(parent_to_child[1]);
        close(child_to_parent[0]);
    } else {
        close(parent_to_child[1]);
        close(child_to_parent[0]);

        recv_msg(parent_to_child[0], buffer, sizeof(buffer), "Child");
        send_msg(child_to_parent[1], child_msg, "Child");

        close(parent_to_child[0]);
        close(child_to_parent[1]);
    }

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/16$ gcc 16.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/16$ ./a.out
Parent: Sent message: Hello, child!
Child: Received message: Hello, child!
Child: Sent message: Hello, parent!
Parent: Received message: Hello, parent!
============================================================================
*/