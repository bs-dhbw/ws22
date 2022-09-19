#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NR_OF_THREADS 3

void *Thread2(void *vargp){
    printf("Hello");
    return NULL;
}

void *Thread1(void *vargp){
    pthread_t thread_id; 
    printf("Hello");
    pthread_create(&thread_id, NULL, Thread2, NULL);
    pthread_join(thread_id, NULL);
    return NULL;
}

int main(void)
{
    pthread_t thread_id[NR_OF_THREADS];

    for (int i = 0; i < NR_OF_THREADS; i++){
      pthread_create(&thread_id[i], NULL, Thread1, NULL);
    }
   
    for (int i = 0; i < NR_OF_THREADS; i++){
       pthread_join(thread_id[i], NULL);
    }

    exit(0);
}
