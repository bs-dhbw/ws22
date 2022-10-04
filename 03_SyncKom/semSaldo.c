#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

// for i in {1..100} ; do ./a.out; done;
sem_t mutex;
float saldo = 25.50;
float expectedSaldo = 26.10;

void *threadA(void *arg) {
  sem_wait(&mutex);
  saldo = saldo + 5.10;
  sem_post(&mutex);
  return 0;
}

void *threadB(void *arg) {
  sem_wait(&mutex);
  saldo = saldo - 4.50;
  sem_post(&mutex);
  return 0;
}

int main() {
  sem_init(&mutex, 0, 1);

  pthread_t t1, t2;
  printf("Saldo at start: %2.2f\n", saldo);
  pthread_create(&t1, NULL, threadA, NULL);
  pthread_create(&t2, NULL, threadB, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  sem_destroy(&mutex);

  printf("Saldo at end: %2.2f\n", saldo);

  assert(saldo == expectedSaldo);
  return 0;
}
