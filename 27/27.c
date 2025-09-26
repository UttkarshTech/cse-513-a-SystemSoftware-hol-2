/*
============================================================================
Name : 27.c
Author : Uttkarsh Ranjan
Description : Write a program to receive messages from the message queue.
                    a. with 0 as a flag
                    b. with IPC_NOWAIT as a flag
Date: 22nd September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

struct packet {
    long type;
    char body[100];
};

int main(int argc, char *argv[]) {
    key_t token;
    int qid;
    struct packet pkt;
    int mode = 0;

    if (argc > 1 && strcmp(argv[1], "nowait") == 0) {
        mode = IPC_NOWAIT;
    }

    token = ftok(".", 65);
    if (token == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    qid = msgget(token, 0666 | IPC_CREAT);
    if (qid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    if (msgrcv(qid, &pkt, sizeof(pkt.body), 1, mode) == -1) {
        perror("msgrcv");
        if (mode == IPC_NOWAIT) {
            puts("Queue is empty (non-blocking).");
        }
        exit(EXIT_FAILURE);
    }

    printf("Received: %s\n", pkt.body);
    return 0;
}

/*
============================================================================
---TERMINAL 1---
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/27$ gcc 27_aux.c -o aux.out
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/27$ gcc 27.c 
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/27$ ./a.out

---TERMINAL 2---
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/27$ ./aux.out
Message sent: HELLO IIITB!

---TERMINAL 1---
Received: HELLO IIITB!
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/27$ ./a.out nowait
msgrcv: No message of desired type
Queue is empty (non-blocking).

---TERMINAL 2---
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/27$ ./aux.out
Message sent: HELLO IIITB!

---TERMINAL 1---
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/27$ ./a.out nowait
Received: HELLO IIITB!
============================================================================
*/