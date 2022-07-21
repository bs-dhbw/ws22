#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
 
 
void *ThreadHello(void *x) {
  usleep(rand() % 500);
  printf("Hello");
  return NULL;
}
 
void *ThreadWorld(void *x) {
  usleep(rand() % 500);
  printf("World");
  return NULL;
}
 
int main(void) {
  pthread_t t[2];
  
  srand(time(NULL));

  pthread_create(&t[1], NULL, ThreadWorld, NULL);
  pthread_create(&t[0], NULL, ThreadHello, NULL);
  pthread_join(t[0], NULL);
  pthread_join(t[1], NULL);
}