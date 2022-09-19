#include <pthread.h>
#include <stdio.h>

int SharedVal;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *Thread1(void *x) {
  pthread_mutex_lock(&mutex);
  SharedVal++;
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int main() {
  pthread_t t[2];
  pthread_create(&t[0], NULL, Thread1, NULL);
  pthread_create(&t[1], NULL, Thread1, NULL);
  pthread_join(t[0], NULL);
  pthread_join(t[1], NULL);
}
