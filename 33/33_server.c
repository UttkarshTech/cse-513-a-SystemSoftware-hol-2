/*
============================================================================
Name : 33_server.c
Author : Uttkarsh Ranjan
Description : Write a program to communicate between two machines using socket.
Date: 22nd September 2025
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 8080
#define BUFFER_LEN 1024

int create_socket() {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    return sock_fd;
}

void bind_socket(int sock_fd, int port, struct sockaddr_in *addr) {
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(port);

    if (bind(sock_fd, (struct sockaddr *)addr, sizeof(*addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

int accept_client(int server_fd, struct sockaddr_in *client_addr) {
    socklen_t addr_len = sizeof(*client_addr);
    int client_fd = accept(server_fd, (struct sockaddr *)client_addr, &addr_len);
    if (client_fd < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    return client_fd;
}

int main() {
    int server_fd = create_socket();
    struct sockaddr_in server_addr, client_addr;

    bind_socket(server_fd, SERVER_PORT, &server_addr);

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", SERVER_PORT);

    int client_fd = accept_client(server_fd, &client_addr);
    printf("Connection accepted from %s:%d\n",
           inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    char buffer[BUFFER_LEN] = {0};
    read(client_fd, buffer, BUFFER_LEN);
    printf("Message from client: %s\n", buffer);

    char *response = "Message received by server";
    send(client_fd, response, strlen(response), 0);

    close(client_fd);
    close(server_fd);
    return 0;
}

/*
============================================================================
---SERVER---
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/33$ gcc 33_server.c -o 33_server.out
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/33$ gcc 33_client.c -o 33_client.out
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/33$ ./33_server.out 
Server listening on port 8080...

---CLIENT---
uttkarsh-ranjan@uttkarsh-ranjan-ubuntu-vm:~/Desktop/SystemSotware/HOL-2/33$ ./33_client.out 

---SERVER---
Connection accepted from 127.0.0.1:34910

---CLIENT---
Message sent to server: Hello from client!

---SERVER---
Message from client: Hello from client!

---CLIENT---
Response from server: Message received by server
============================================================================
*/
