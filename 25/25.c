/*
============================================================================
Name : 25.c
Author : Uttkarsh Ranjan
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
                    a. access permission
                    b. uid, gid
                    c. time of last message sent and received
                    d. time of last change in the message queue
                    e. size of the queue
                    f. number of messages in the queue
                    g. maximum number of bytes allowed
                    h. pid of the msgsnd and msgrcv
Date: 22nd September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

void show_info(struct msqid_ds *info) {
    printf("Message Queue Details:\n");
    printf("a. Permission: %o\n", info->msg_perm.mode);
    printf("b. UID: %d, GID: %d\n", info->msg_perm.uid, info->msg_perm.gid);
    printf("c. Last send: %s", info->msg_stime ? ctime(&info->msg_stime) : "Not yet sent\n");
    printf("   Last receive: %s", info->msg_rtime ? ctime(&info->msg_rtime) : "Not yet received\n");
    printf("d. Change time: %s", ctime(&info->msg_ctime));
    printf("e. Current size: %lu bytes\n", info->__msg_cbytes);
    printf("f. Messages in queue: %lu\n", info->msg_qnum);
    printf("g. Max allowed bytes: %lu\n", info->msg_qbytes);
    printf("h. Last send PID: %d, Last receive PID: %d\n", info->msg_lspid, info->msg_lrpid);
}

int main() {
    key_t k = ftok(".", 65);
    if (k == -1) {
        perror("ftok");
        exit(1);
    }

    int qid = msgget(k, 0666 | IPC_CREAT);
    if (qid == -1) {
        perror("msgget");
        exit(1);
    }

    struct msqid_ds qinfo;
    if (msgctl(qid, IPC_STAT, &qinfo) == -1) {
        perror("msgctl");
        exit(1);
    }

    show_info(&qinfo);
    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/25$ gcc 25.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/25$ ./a.out
Message Queue Details:
a. Permission: 666
b. UID: 1000, GID: 1000
c. Last send: Not yet sent
   Last receive: Not yet received
d. Change time: Fri Sep 19 18:30:28 2025
e. Current size: 0 bytes
f. Messages in queue: 0
g. Max allowed bytes: 16384
h. Last send PID: 0, Last receive PID: 0
============================================================================
*/