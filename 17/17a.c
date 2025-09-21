/*
============================================================================
Name : 17a.c
Author : Uttkarsh Ranjan
Description : Write a program to execute ls -l | wc.
                a. use dup
                b. use dup2
                c. use fcntl
Date: 19th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void redirect_fd(int old_fd, int new_fd) {
    close(new_fd);
    dup(old_fd);
    close(old_fd);
}

int main() {
    int pipe_fds[2];

    if (pipe(pipe_fds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t child_ls = fork();
    if (child_ls < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_ls == 0) {
        close(pipe_fds[0]);
        redirect_fd(pipe_fds[1], STDOUT_FILENO);
        execl("/bin/ls", "ls", "-l", NULL);
        perror("execl ls");
        exit(EXIT_FAILURE);
    }

    pid_t child_wc = fork();
    if (child_wc < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_wc == 0) {
        close(pipe_fds[1]);
        redirect_fd(pipe_fds[0], STDIN_FILENO);
        execl("/usr/bin/wc", "wc", NULL);
        perror("execl wc");
        exit(EXIT_FAILURE);
    }

    close(pipe_fds[0]);
    close(pipe_fds[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/17$ gcc 17a.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/17$ ./a.out
      5      38     289
============================================================================
*/