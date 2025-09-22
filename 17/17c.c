/*
============================================================================
Name : 17c.c
Author : Uttkarsh Ranjan
Description : Write a program to execute ls -l | wc.
                a. use dup
                b. use dup2
                c. use fcntl
Date: 20th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t child1 = fork();
    if (child1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        execl("/bin/ls", "ls", "-l", NULL);
        perror("execl ls");
        exit(EXIT_FAILURE);
    }

    pid_t child2 = fork();
    if (child2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child2 == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        execl("/usr/bin/wc", "wc", NULL);
        perror("execl wc");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/17$ gcc 17c.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/17$ ./a.out
      5      38     289
============================================================================
*/