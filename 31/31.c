/*
============================================================================
Name : 31.c
Author : Uttkarsh Ranjan
Description : Write a program to create a semaphore and initialize value to the semaphore.
                    a. create a binary semaphore
                    b. create a counting semaphore
Date: 20th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

key_t generate_key(int proj_id) {
    key_t token = ftok(".", proj_id);
    if (token == -1) handle_error("ftok");
    return token;
}

int create_semaphore(key_t token, int num_sems) {
    int id = semget(token, num_sems, 0666 | IPC_CREAT);
    if (id == -1) handle_error("semget");
    return id;
}

void initialize_semaphore(int semid, int sem_num, int init_val) {
    union semun sem_union;
    sem_union.val = init_val;
    if (semctl(semid, sem_num, SETVAL, sem_union) == -1) handle_error("semctl SETVAL");
}

int main() {
    key_t key_bin = generate_key(65);
    int semid_bin = create_semaphore(key_bin, 1);
    initialize_semaphore(semid_bin, 0, 1);
    printf("Binary semaphore created with ID %d and initialized to 1\n", semid_bin);

    int resources = 5;
    key_t key_count = generate_key(66); // different key for counting semaphore
    int semid_count = create_semaphore(key_count, 1);
    initialize_semaphore(semid_count, 0, resources);
    printf("Counting semaphore created with ID %d and initialized to %d\n", semid_count, resources);

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/31$ gcc 31.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/31$ ./a.out
Binary semaphore created with ID 0 and initialized to 1
Counting semaphore created with ID 1 and initialized to 5
============================================================================
*/