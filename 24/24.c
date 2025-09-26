/*
============================================================================
Name : 24.c
Author : Uttkarsh Ranjan
Description : Write a program to create a message queue and print the key and message queue id.
Date: 20th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

key_t create_key(const char *path, int proj) {
    key_t k = ftok(path, proj);
    if (k == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    return k;
}

int create_queue(key_t k) {
    int qid = msgget(k, 0666 | IPC_CREAT);
    if (qid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    return qid;
}

void remove_queue(int qid) {
    if (msgctl(qid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
    printf("Message Queue with ID %d deleted successfully!\n", qid);
}

int main() {
    key_t k = create_key(".", 65);
    int qid = create_queue(k);

    printf("Message Queue created successfully!\n");
    printf("Key: %d\n", k);
    printf("Message Queue ID: %d\n", qid);

    remove_queue(qid);

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/24$ gcc 24.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/24$ ./a.out
Message Queue created successfully!
Key: 1090654448
Message Queue ID: 0
Message Queue with ID 0 deleted successfully!
============================================================================
*/