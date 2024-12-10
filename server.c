#include "./headers/socket/socket_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func(int connfd) {
  char buff[MAX];
  int n;

  // Infinite loop for chat
  while (1) {
    bzero(buff, MAX);

    // Read message from client
    read(connfd, buff, sizeof(buff));
    printf("From client: %s\t To client: ", buff);

    // Clear buffer and get server response
    bzero(buff, MAX);
    n = 0;
    while ((buff[n++] = getchar()) != '\n')
      ;

    // Send response to client
    write(connfd, buff, sizeof(buff));

    // Exit condition
    if (strncmp("exit", buff, 4) == 0) {
      printf("Server Exit...\n");
      break;
    }
  }
}

int main() {
  int sockfd, connfd;
  struct sockaddr_in cli;
  socklen_t len = sizeof(cli);

  // Setup server socket
  sockfd = setup_server_socket();

  // Accept a client connection
  connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
  if (connfd < 0) {
    perror("Server accept failed");
    close(sockfd);
    return EXIT_FAILURE;
  }
  printf("Server accepted the client\n");

  // Chat function
  func(connfd);

  // Close the socket
  close(connfd);
  close(sockfd);
  return 0;
}
