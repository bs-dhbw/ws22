#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NR_OF_THREADS 3

void *myThread(void *vargp)
{
    int *threadNrPtr = (int*) vargp; 

    sleep(rand() % 5);
    printf("HelloWorld from Thread %d \n", *threadNrPtr);
    return NULL;
}


int main (void)
{
  srand(time(NULL));

 pthread_t thread_id[NR_OF_THREADS];

    for (int i = 0; i < NR_OF_THREADS; i++)
    {
      pthread_create(&thread_id[i], NULL, myThread, (void*)&i);
    }
   
    for (int i = 0; i < NR_OF_THREADS; i++)
    {
       pthread_join(thread_id[i], NULL);
    }

}