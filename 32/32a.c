/*
============================================================================
Name : 32a.c
Author : Uttkarsh Ranjan
Description : Write a program to implement semaphore to protect any critical section.
                    a. rewrite the ticket number creation program using semaphore
                    b. protect shared memory from concurrent write access
                    c. protect multiple pseudo resources ( may be two) using counting semaphore
                    d. remove the created semaphore
Date: 22nd September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

static void semaphore_lock(int semid) {
    struct sembuf op = {0, -1, 0};
    if (semop(semid, &op, 1) == -1) {
        perror("semop lock");
        exit(EXIT_FAILURE);
    }
}

static void semaphore_unlock(int semid) {
    struct sembuf op = {0, 1, 0};
    if (semop(semid, &op, 1) == -1) {
        perror("semop unlock");
        exit(EXIT_FAILURE);
    }
}

static void setup_file(const char *path) {
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open (init)");
        exit(EXIT_FAILURE);
    }
    int start = 0;
    if (write(fd, &start, sizeof(start)) != sizeof(start)) {
        perror("write (init)");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
}

int main() {
    const char *filename = "32_tickets.bin";

    key_t key = ftok(filename, 42);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    int semid = semget(key, 1, 0666 | IPC_CREAT | IPC_EXCL);
    if (semid != -1) {
        union semun arg;
        arg.val = 1;
        if (semctl(semid, 0, SETVAL, arg) == -1) {
            perror("semctl init");
            exit(EXIT_FAILURE);
        }
        setup_file(filename);
    } else if (errno == EEXIST) {
        semid = semget(key, 1, 0666);
        if (semid == -1) {
            perror("semget attach");
            exit(EXIT_FAILURE);
        }
    } else {
        perror("semget");
        exit(EXIT_FAILURE);
    }
    
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("open tickets.bin");
        exit(EXIT_FAILURE);
    }

    semaphore_lock(semid);

    int ticket;
    if (read(fd, &ticket, sizeof(ticket)) != sizeof(ticket)) {
        perror("read ticket");
        close(fd);
        semaphore_unlock(semid);
        exit(EXIT_FAILURE);
    }

    ticket++;
    printf("Your reserved ticket number is: %d\n", ticket);

    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        semaphore_unlock(semid);
        exit(EXIT_FAILURE);
    }

    if (write(fd, &ticket, sizeof(ticket)) != sizeof(ticket)) {
        perror("write ticket");
        close(fd);
        semaphore_unlock(semid);
        exit(EXIT_FAILURE);
    }

    semaphore_unlock(semid);
    close(fd);

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/32$ gcc 32a.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/32$ touch 32_tickets.bin
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/32$ ./a.out
Your reserved ticket number is: 1
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/32$ ./a.out
Your reserved ticket number is: 2
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/32$ ./a.out
Your reserved ticket number is: 3
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/32$ ./a.out
Your reserved ticket number is: 4
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/32$ ./a.out
Your reserved ticket number is: 5
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/32$ ./a.out
Your reserved ticket number is: 6
============================================================================
*/
