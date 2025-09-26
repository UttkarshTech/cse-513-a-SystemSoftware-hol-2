/*
============================================================================
Name : 34_client.c
Author : Uttkarsh Ranjan
Description :34. Write a program to create a concurrent server.
                a. use fork
                b. use pthread_create
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
#define SERVER_IP "127.0.0.1"

int create_client_socket() {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    return sock_fd;
}

void connect_to_server(int sock_fd, const char *ip, int port, struct sockaddr_in *addr) {
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &addr->sin_addr) <= 0) {
        perror("Invalid server address");
        exit(EXIT_FAILURE);
    }

    if (connect(sock_fd, (struct sockaddr *)addr, sizeof(*addr)) < 0) {
        perror("Connection to server failed");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int sock_fd = create_client_socket();
    struct sockaddr_in server_addr;

    connect_to_server(sock_fd, SERVER_IP, SERVER_PORT, &server_addr);

    char *msg = "Hello from client!";
    send(sock_fd, msg, strlen(msg), 0);
    printf("Message sent to server: %s\n", msg);

    char buffer[BUFFER_LEN] = {0};
    read(sock_fd, buffer, BUFFER_LEN);
    printf("Response from server: %s\n", buffer);
    
    sleep(10);
    
    close(sock_fd);
    return 0;
}
