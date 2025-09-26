/*
============================================================================
Name : 22.c
Author : Uttkarsh Ranjan
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
Date: 22nd September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

int create_fifo(const char *path) {
    if (mkfifo(path, 0666) == -1) {
        perror("mkfifo (ignore if already exists)");
    }
    return 0;
}

int open_fifo_read(const char *path) {
    int fd = open(path, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    return fd;
}

void wait_for_data(int fd) {
    fd_set rfds;
    struct timeval tv;
    char buf[100];

    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    tv.tv_sec = 10;
    tv.tv_usec = 0;

    printf("Waiting for data in FIFO for up to 10 seconds...\n");

    int ret = select(fd + 1, &rfds, NULL, NULL, &tv);
    if (ret == -1) {
        perror("select");
        exit(EXIT_FAILURE);
    } else if (ret == 0) {
        printf("Timeout: No data written to FIFO within 10 seconds.\n");
    } else {
        if (FD_ISSET(fd, &rfds)) {
            int n = read(fd, buf, sizeof(buf) - 1);
            if (n > 0) {
                buf[n] = '\0';
                printf("Data received from FIFO: %s\n", buf);
            } else {
                printf("FIFO opened but no data available.\n");
            }
        }
    }
}

int main() {
    const char *fifo = "22_fifo";

    create_fifo(fifo);
    int fd = open_fifo_read(fifo);

    wait_for_data(fd);

    close(fd);
    unlink(fifo);
    return 0;
}


/*
============================================================================
---TERMINAL 1---
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/22$ gcc 22.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/22$ mkfifo 22_fifo
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/22$ ./a.out
Waiting for data in FIFO for up to 10 seconds...
Timeout: No data written to FIFO within 10 seconds.
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/22$ ./a.out
Waiting for data in FIFO for up to 10 seconds...

---TERMINAL 2---
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/22$ echo "Hello IIITB" > 22_fifo

---TERMINAL 1---
Data received from FIFO: Hello IIITB
============================================================================
*/