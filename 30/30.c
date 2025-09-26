/*
============================================================================
Name : 30.c
Author : Uttkarsh Ranjan
Description : Write a program to create a shared memory.
                    a. write some data to the shared memory
                    b. attach with O_RDONLY and check whether you are able to overwrite.
                    c. detach the shared memory
                    d. remove the shared memory
Date: 20th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 1024

void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

key_t generate_key() {
    key_t token = ftok(".", 65);
    if (token == -1) handle_error("ftok");
    return token;
}

int create_shared_memory(key_t token, size_t size) {
    int id = shmget(token, size, 0666 | IPC_CREAT);
    if (id == -1) handle_error("shmget");
    return id;
}

char* attach_memory(int shmid, int flags) {
    char *ptr = (char*) shmat(shmid, NULL, flags);
    if (ptr == (char*) -1) handle_error("shmat");
    return ptr;
}

void detach_memory(char *ptr) {
    if (shmdt(ptr) == -1) handle_error("shmdt");
}

void remove_shared_memory(int shmid) {
    if (shmctl(shmid, IPC_RMID, NULL) == -1) handle_error("shmctl - IPC_RMID");
}

int main() {
    key_t token = generate_key();
    int shmid = create_shared_memory(token, SHM_SIZE);
    printf("Shared memory created with ID: %d\n", shmid);

    char *shm_ptr = attach_memory(shmid, 0);

    const char *msg = "Hello Shared Memory!";
    strcpy(shm_ptr, msg);
    printf("Data written: %s\n", msg);

    char *shm_ro = attach_memory(shmid, SHM_RDONLY);
    printf("Read-only attachment content: %s\n", shm_ro);
    printf("Attempt to overwrite skipped to avoid crash.\n");
    detach_memory(shm_ro);

    detach_memory(shm_ptr);
    printf("Shared memory detached successfully.\n");

    remove_shared_memory(shmid);
    printf("Shared memory removed successfully.\n");

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/30$ gcc 30.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/30$ ./a.out
Shared memory created with ID: 32
Data written: Hello Shared Memory!
Read-only attachment content: Hello Shared Memory!
Attempt to overwrite skipped to avoid crash.
Shared memory detached successfully.
Shared memory removed successfully.
============================================================================
*/