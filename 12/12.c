/*
============================================================================
Name : 12.c
Author : Uttkarsh Ranjan
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to
the parent process from the child process.
Date: 20th September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void child_process() {
    printf("Child: PID = %d, Parent PID = %d\n", getpid(), getppid());
    printf("Child: Sending SIGKILL to parent (PID = %d)\n", getppid());
    kill(getppid(), SIGKILL);
    sleep(2);
    printf("Child: New Parent PID = %d\n", getppid());
    exit(0);
}

void parent_process(pid_t child_pid) {
    printf("Parent: PID = %d, Child PID = %d\n", getpid(), child_pid);
    sleep(10);
    printf("Parent: Still alive\n");
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        child_process();
    } else {
        parent_process(pid);
    }

    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/12$ gcc 12.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/12$ ./a.out
Parent: PID = 23250, Child PID = 23251
Child: PID = 23251, Parent PID = 23250
Child: Sending SIGKILL to parent (PID = 23250)
Killed
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/12$ Child: New Parent PID = 1836
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSoftware/HOL-2/12$ ps -ef | grep systemd | grep 1836
uttkars+    1836       1  0 Sep18 ?        00:00:00 /usr/lib/systemd/systemd --user
uttkars+    1870    1836  0 Sep18 ?        00:00:00 /usr/bin/dbus-daemon --session --address=systemd: --nofork --nopidfile --systemd-activation --syslog-only
uttkars+    2057    1836  0 Sep18 ?        00:00:00 /usr/libexec/gnome-session-binary --systemd-service --session=ubuntu
============================================================================
*/