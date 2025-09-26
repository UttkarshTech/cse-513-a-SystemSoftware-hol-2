/*
============================================================================
Name : 21_1.c
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
    printf("Process1 sent: %s", msg);
}

void receive_message(int fd, char *buf, size_t size) {
    int n = read(fd, buf, size - 1);
    if (n > 0) {
        buf[n] = '\0';
        printf("Process1 received: %s", buf);
    }
}

int main() {
    const char *path1 = "21_fifo_1";
    const char *path2 = "21_fifo_2";
    char buf[100];

    int fd_write = open_fifo(path1, O_WRONLY);
    int fd_read  = open_fifo(path2, O_RDONLY);

    const char *msg = "Hello from Process 1!\n";
    send_message(fd_write, msg);
    receive_message(fd_read, buf, sizeof(buf));

    close(fd_write);
    close(fd_read);
    return 0;
}

/*
============================================================================
---TERMINAL 1---
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/21$ gcc 21_1.c -o 21_1.out
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/21$ gcc 21_2.c -o 21_2.out
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/21$ mkfifo 21_fifo_{1..2}
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/21$ ./21_1.out

---TERMINAL 2---
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/21$ ./21_2.out

---TERMINAL 1---
Process1 sent: Hello from Process 1!
Process1 received: Hello from Process 2!

---TERMINAL 2---
Process2 received: Hello from Process 1!
Process2 sent: Hello from Process 2!
============================================================================
*/