#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
// TODO upload
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
bool HelloDone = false;

void *Th_Hello(void *vargp) {
  usleep(rand() % 1000);
  printf("Hello");

  pthread_mutex_lock(&lock);
  HelloDone = true;
  pthread_cond_signal(&cond1);
  pthread_mutex_unlock(&lock);

  return NULL;
}

void *Th_World(void *vargp) {
  pthread_mutex_lock(&lock);

  while (HelloDone == false) {
    pthread_cond_wait(&cond1, &lock);
  }

  usleep(rand() % 1000);
  printf("World\n");

  pthread_mutex_unlock(&lock);
  return NULL;
}

int main(void) {
  pthread_t tid_Hello, tid_World;
  srand(time(NULL));

  pthread_create(&tid_Hello, NULL, Th_Hello, NULL);
  pthread_create(&tid_World, NULL, Th_World, NULL);

  pthread_join(tid_Hello, NULL);
  pthread_join(tid_World, NULL);

  exit(0);
}
