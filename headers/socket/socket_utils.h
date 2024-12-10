#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H

#include <netinet/in.h> // For sockaddr_in
#include <sys/socket.h> // For socket functions
#include <unistd.h>     // For close()

#define PORT 8080 // Server port
#define MAX 1024  // Buffer size

int setup_server_socket(); // Function to create and configure the server socket

#endif
