/*
============================================================================
Name : 32d.c
Author : Uttkarsh Ranjan
Description : Write a program to implement semaphore to protect any critical section.
                    a. rewrite the ticket number creation program using semaphore
                    b. protect shared memory from concurrent write access
                    c. protect multiple pseudo resources ( may be two) using counting semaphore
                    d. remove the created semaphore
Date: 20th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

int main() {
    key_t sem_key = ftok(".", 65);
    if (sem_key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    int sem_identifier = semget(sem_key, 1, 0666 | IPC_CREAT);
    if (sem_identifier == -1) {
          perror("semget");
          exit(EXIT_FAILURE);
    }
    printf("Semaphore successfully created\n");

    if (semctl(sem_identifier, 0, IPC_RMID) == -1) {
        perror("semctl remove");
        exit(EXIT_FAILURE);
    }

    printf("Semaphore successfully deleted\n");
    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/32$ gcc 32d.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/32$ ./a.out
Semaphore successfully created
Semaphore successfully deleted
============================================================================
*/
