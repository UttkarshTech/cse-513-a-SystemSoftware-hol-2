/*
============================================================================
Name : 20_1.c
Author : Uttkarsh Ranjan
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 20th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void send_message(const char *fifo_path, const char *msg) {
    int fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (write(fd, msg, strlen(msg)) == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
}

int main() {
    const char *fifo_path = "20_fifo";
    const char *msg = "Hello from Writer!\n";

    send_message(fifo_path, msg);
    printf("Message sent: %s", msg);

    return 0;
}

/*
============================================================================
---TERMINAL 1---
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/20$ mkfifo 20_fifo
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/20$ gcc 20_1.c -o 20_1.out
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/20$ gcc 20_2.c -o 20_2.out
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/20$ ./20_1.out

---TERMINAL 2---
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/20$ ./20_2.out

---TERMINAL 1---
Message sent: Hello from Writer!

---TERMINAL 2---
Message received: Hello from Writer!
============================================================================
*/