/*
============================================================================
Name : 21_2.c
Author : Uttkarsh Ranjan
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 20th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int open_fifo(const char *path, int mode) {
    int fd = open(path, mode);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    return fd;
}

void send_message(int fd, const char *msg) {
    write(fd, msg, strlen(msg));
    printf("Process2 sent: %s", msg);
}

void receive_message(int fd, char *buf, size_t size) {
    int n = read(fd, buf, size - 1);
    if (n > 0) {
        buf[n] = '\0';
        printf("Process2 received: %s", buf);
    }
}

int main() {
    const char *path1 = "21_fifo_1";
    const char *path2 = "21_fifo_2";
    char buf[100];

    int fd_read  = open_fifo(path1, O_RDONLY);
    int fd_write = open_fifo(path2, O_WRONLY);

    receive_message(fd_read, buf, sizeof(buf));

    const char *msg = "Hello from Process 2!\n";
    send_message(fd_write, msg);

    close(fd_read);
    close(fd_write);
    return 0;
}

