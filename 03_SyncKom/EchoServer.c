#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
/*
 * Fragen:
 * 1) Was passiert bei mehrer Client Verbindungen?
 * 2) Was passiert wenn der Server abstürzt bzw. die Shell beendet wird
 * 3) Was passiert bei CTRL+C
 * 4) Was passiert wenn der Client eine Nachricht > 100 Bytes schickt
 * 5) Wie schaut die CPU Last des Programms aus?
 *
 */
int main() {

  char str[100];
  int listen_fd, comm_fd;

  struct sockaddr_in servaddr;

  listen_fd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htons(INADDR_ANY);
  servaddr.sin_port = htons(4444);

  bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));

  listen(listen_fd, 10);

  comm_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);
  printf("Accepted new connection\n");
  while (1) {

    bzero(str, 100);

    read(comm_fd, str, 100);

    printf("Echoing back - %s", str);

    write(comm_fd, str, strlen(str) + 1);
  }
}