/*
============================================================================
Name : 18.c
Author : Uttkarsh Ranjan
Description : Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.
Date: 20th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void spawn_process(int input_fd, int output_fd, const char *path, char *const args[]) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        if (input_fd != -1) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd != -1) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }
        execlp(path, args[0], args[1], args[2], NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int pipe_ls_grep[2], pipe_grep_wc[2];

    if (pipe(pipe_ls_grep) == -1 || pipe(pipe_grep_wc) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    char *ls_args[] = {"ls", "-l", NULL};
    char *grep_args[] = {"grep", "^d", NULL};
    char *wc_args[] = {"wc", NULL, NULL};

    spawn_process(-1, pipe_ls_grep[1], "/bin/ls", ls_args);
    close(pipe_ls_grep[1]);

    spawn_process(pipe_ls_grep[0], pipe_grep_wc[1], "/bin/grep", grep_args);
    close(pipe_ls_grep[0]);
    close(pipe_grep_wc[1]);

    spawn_process(pipe_grep_wc[0], -1, "/usr/bin/wc", wc_args);
    close(pipe_grep_wc[0]);

    for (int i = 0; i < 3; i++)
        wait(NULL);

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/18$ gcc 18.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/18$ ./a.out
      0       0       0
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/18$ mkdir test{1..10}
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/18$ ./a.out
     10      90     701
============================================================================
*/