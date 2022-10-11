#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void catcher(int sigtype) {
  printf("Received signal: %d\n", sigtype);

  if (sigtype == SIGINT) {
    printf("gracefully shutdown...\n");
    exit(EXIT_SUCCESS);
  }
}

int main() {
  signal(SIGINT, catcher);

  printf("Own PID: %d\n", getpid());

  for (int i = 1; i < 100; i++) {
    printf("Working...\n");
    sleep(1);
  }
}