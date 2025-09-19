/*
============================================================================
Name : 9.c
Author : Uttkarsh Ranjan
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.
Date: 19th September 2025
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    printf("Phase 1: SIGINT (Ctrl+C) will be ignored for 5 seconds...\n");

    signal(SIGINT, SIG_IGN);

    for (int sec = 5; sec > 0; sec--) {
        printf("%d...\n", sec);
        sleep(1);
    }

    printf("Phase 2: Restoring default behavior for SIGINT.\n");

    signal(SIGINT, SIG_DFL);

    printf("Press Ctrl+C now to terminate the program.\n");

    while (1) {
        sleep(1);
        printf("Program running...\n");
    }

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/9$ gcc 9.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/9$ ./a.out
Phase 1: SIGINT (Ctrl+C) will be ignored for 5 seconds...
5...
4...
3...
2...
1...
Phase 2: Restoring default behavior for SIGINT.
Press Ctrl+C now to terminate the program.
Program running...
Program running...
Program running...
Program running...
^C
============================================================================
*/
