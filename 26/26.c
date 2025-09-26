/*
============================================================================
Name : 26.c
Author : Uttkarsh Ranjan
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 22nd September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long type;
    char text[100];
};

void send_msg(int qid, const char *data) {
    struct message m;
    m.type = 1;
    strncpy(m.text, data, sizeof(m.text) - 1);
    m.text[sizeof(m.text) - 1] = '\0';

    if (msgsnd(qid, &m, sizeof(m.text), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    printf("Message delivered: %s\n", m.text);
}

int main() {
    key_t token = ftok(".", 65);
    if (token == -1) {
        perror("ftok");
        exit(1);
    }

    int qid = msgget(token, 0666 | IPC_CREAT);
    if (qid == -1) {
        perror("msgget");
        exit(1);
    }

    send_msg(qid, "Hello from message queue!");
    return 0;
}

/*
============================================================================
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/26$ gcc 26.c
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/26$ ./a.out
Message delivered: Hello from message queue!
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/26$ ./a.out
Message delivered: Hello from message queue!
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/26$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x410210f2 1          uttkarsh-r 666        0            0           
0x410210f4 2          uttkarsh-r 666        200          2           

uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/26$ ./a.out
Message delivered: Hello from message queue!
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/26$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x410210f2 1          uttkarsh-r 666        0            0           
0x410210f4 2          uttkarsh-r 666        300          3      
============================================================================
*/