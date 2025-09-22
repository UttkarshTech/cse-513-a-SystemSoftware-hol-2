/*
============================================================================
Name : 13_1.c
Author : Uttkarsh Ranjan
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program
will send the signal (using kill system call). Find out whether the first program is able to catch
the signal or not.
Date: 20th September 2025
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught signal %d\n", sig);
}

int main() {
    signal(SIGSTOP, handler);

    printf("PID = %d. Waiting for SIGSTOP...\n", getpid());

    while (1) {
        sleep(1);
    }

    return 0;
}

/*
============================================================================
---TERMINAL 1---
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/12$ cd ../13
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/13$ gcc 13_1.c -o 13_1.out
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/13$ gcc 13_2.c -o 13_2.out
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/13$ ./13_1.out
PID = 23533. Waiting for SIGSTOP...

---TERMINAL 2---
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/13$ ./13_2.out 23533
Sending SIGSTOP to process 23533
SIGSTOP sent successfully.

---TERMINAL 1---

[1]+  Stopped                 ./13_1.out


NOTE : THE CATCH WILL NOT WORK WITH SIGSTOP. IT WILL WORK WITH SIGINT.
SIGSTOP CANNOT BE CAUGHT, BLOCKED OR IGNORED.
============================================================================
*/
