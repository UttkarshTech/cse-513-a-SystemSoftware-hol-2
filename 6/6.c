/*
============================================================================
Name : 6.c
Author : Uttkarsh Ranjan
Description : Write a simple program to create three threads.
Date: 19th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* run_task(void* arg) {
    int idx = *((int*)arg);
    printf("Hello from thread %d (TID: %lu)\n", idx, pthread_self());
    sleep(1);
    return NULL;
}

int main() {
    pthread_t workers[3];
    int ids[3];

    for (int i = 0; i < 3; i++) {
        ids[i] = i + 1;
        if (pthread_create(&workers[i], NULL, run_task, &ids[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(workers[i], NULL);
    }

    printf("All threads completed.\n");
    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/6$ gcc 6.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/6$ ./a.out
Hello from thread 1 (TID: 127162195637952)
Hello from thread 2 (TID: 127162187245248)
Hello from thread 3 (TID: 127162178852544)
All threads completed.
============================================================================
*/
