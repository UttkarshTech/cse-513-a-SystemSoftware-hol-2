/*
============================================================================
Name : 13_2.c
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
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    pid_t target_pid = (pid_t)atoi(argv[1]);
    printf("Sending SIGSTOP to process %d\n", target_pid);

    if (kill(target_pid, SIGSTOP) == -1) {
        perror("Failed to send SIGSTOP");
        return 1;
    }

    printf("SIGSTOP sent successfully.\n");
    return 0;
}
