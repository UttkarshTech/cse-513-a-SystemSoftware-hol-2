/*
============================================================================
Name : 28.c
Author : Uttkarsh Ranjan
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date: 20th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

void update_mode(int q, mode_t new_mode) {
    struct msqid_ds buf;
    if (msgctl(q, IPC_STAT, &buf) == -1) {
        perror("msgctl - get");
        exit(EXIT_FAILURE);
    }

    printf("Old mode: %o\n", buf.msg_perm.mode);
    buf.msg_perm.mode = new_mode;

    if (msgctl(q, IPC_SET, &buf) == -1) {
        perror("msgctl - set");
        exit(EXIT_FAILURE);
    }

    if (msgctl(q, IPC_STAT, &buf) == -1) {
        perror("msgctl - verify");
        exit(EXIT_FAILURE);
    }
    printf("New mode: %o\n", buf.msg_perm.mode);
}

int main() {
    key_t k = ftok(".", 65);
    if (k == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    int q = msgget(k, 0666 | IPC_CREAT);
    if (q == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    update_mode(q, 0644);
    return 0;
}


/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/28$ gcc 28.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/28$ ./a.out
Old mode: 666
New mode: 644
============================================================================
*/