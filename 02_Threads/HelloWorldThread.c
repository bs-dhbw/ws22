#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool HelloDone = false;

void *ThreadHello(void *arg) {
  printf("Hello");
  sleep(100);
  HelloDone = true;
  pthread_exit(0);
}

void *ThreadWorld(void *arg) {
  while (HelloDone != true) {
    // Spinnlock
    // wait
    printf("wait...\n");
  }
  printf("World\n");
  pthread_exit(0);
}

int main(void) {
  pthread_t ThreadIdHello;
  pthread_t ThreadIdWorld;

  /* Fire up Hello thread and wait until complete */
  pthread_create(&ThreadIdHello, NULL, ThreadHello, NULL);
  /* Fire up World thread and wait until complete */
  pthread_create(&ThreadIdWorld, NULL, ThreadWorld, NULL);

  usleep(100);

  pthread_join(ThreadIdWorld, NULL);
  pthread_join(ThreadIdHello, NULL);

  exit(0);
}