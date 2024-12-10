#include "socket_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int setup_server_socket() {
  int sockfd;
  struct sockaddr_in servaddr;

  // Create socket file descriptor
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }
  printf("Socket successfully created\n");

  // Zero out the server address structure
  bzero(&servaddr, sizeof(servaddr));

  // Assign IP and PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  // Bind the socket to the address
  if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
    perror("Socket bind failed");
    close(sockfd);
    exit(EXIT_FAILURE);
  }
  printf("Socket successfully binded\n");

  // Start listening for connections
  if (listen(sockfd, 5) != 0) {
    perror("Listen failed");
    close(sockfd);
    exit(EXIT_FAILURE);
  }
  printf("Server is listening on port %d\n", PORT);

  return sockfd;
}
