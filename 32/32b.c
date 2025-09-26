/*
============================================================================
Name : 32b.c
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
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <errno.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void acquire_sem(int sid) {
    int val = semctl(sid, 0, GETVAL);
    if (val == 0) {
        printf("Process %d waiting for semaphore...\n", getpid());
        fflush(stdout);
    }
    struct sembuf op = {0, -1, 0};
    if (semop(sid, &op, 1) == -1) {
        perror("semop acquire");
        exit(EXIT_FAILURE);
    }
}

void release_sem(int sid) {
    struct sembuf op = {0, 1, 0};
    if (semop(sid, &op, 1) == -1) {
        perror("semop release");
        exit(EXIT_FAILURE);
    }
}

int init_semaphore(key_t token) {
    int semid = semget(token, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }
    int val = semctl(semid, 0, GETVAL);
    if (val == -1 && errno == EINVAL) {
        union semun arg;
        arg.val = 1;
        if (semctl(semid, 0, SETVAL, arg) == -1) {
            perror("semctl setval");
            exit(EXIT_FAILURE);
        }
    }
    return semid;
}

int init_shared_memory(key_t token) {
    int id = shmget(token, 1024, 0666 | IPC_CREAT);
    if (id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    return id;
}

int main() {
    key_t key = ftok(".", 65);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    int shm_id = init_shared_memory(key);
    char *shared_ptr = (char*) shmat(shm_id, NULL, 0);
    if (shared_ptr == (char*) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    int sem_id = init_semaphore(key);

    acquire_sem(sem_id);
    printf("Process %d writing...\n", getpid());
    snprintf(shared_ptr, 100, "Hello from process %d", getpid());
    sleep(10);
    printf("Process %d done writing.\n", getpid());
    release_sem(sem_id);

    shmdt(shared_ptr);
    return 0;
}

/*
============================================================================
---TERMINAL 1---
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/32$ gcc 32b.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/32$ ./a.out
Process 11695 writing...

---TERMINAL 2---
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/32$ ./a.out
Process 11707 waiting for semaphore...

---TERMINAL 1---
Process 11695 done writing.

---TERMINAL 2---
Process 11707 writing...
Process 11707 done writing.
============================================================================
*/
