/*
============================================================================
Name : 20_2.c
Author : Uttkarsh Ranjan
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 19th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void receive_message(const char *fifo_path, char *buffer, size_t size) {
    int fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int n = read(fd, buffer, size - 1);
    if (n > 0) {
        buffer[n] = '\0';
    } else {
        buffer[0] = '\0';
    }

    close(fd);
}

int main() {
    const char *fifo_path = "20_fifo";
    char buffer[100];

    receive_message(fifo_path, buffer, sizeof(buffer));
    printf("Message received: %s", buffer);

    return 0;
}