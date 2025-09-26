#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct packet {
    long type;
    char data[100];
};

void send_message(int qid, struct packet *pkt) {
    if (msgsnd(qid, pkt, sizeof(pkt->data), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    printf("Message sent: %s\n", pkt->data);
}

int main() {
    key_t k;
    int q;
    struct packet pkt;

    k = ftok(".", 65);
    if (k == -1) {
        perror("ftok");
        exit(1);
    }

    q = msgget(k, 0666 | IPC_CREAT);
    if (q == -1) {
        perror("msgget");
        exit(1);
    }

    pkt.type = 1;
    strcpy(pkt.data, "HELLO IIITB!");
    // printf("Enter message: ");
    // fgets(pkt.data, sizeof(pkt.data), stdin);
    // pkt.data[strcspn(pkt.data, "\n")] = '\0';

    send_message(q, &pkt);
    return 0;
}