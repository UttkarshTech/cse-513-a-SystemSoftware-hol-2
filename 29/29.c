/*
============================================================================
Name : 29.c
Author : Uttkarsh Ranjan
Description : Write a program to remove the message queue.
Date: 20th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t token;
    int qid;

    token = ftok(".", 65);
    if (token == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    printf("Generated key = %d\n", token);

    qid = msgget(token, 0666 | IPC_CREAT);
    if (qid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    if (msgctl(qid, IPC_RMID, NULL) == -1) {
        perror("msgctl (IPC_RMID)");
        exit(EXIT_FAILURE);
    }

    printf("Message queue with ID %d successfully deleted.\n", qid);
    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/29$ gcc 29.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/29$ ./a.out
Generated key = 1090654458
Message queue with ID 5 successfully deleted.
============================================================================
*/