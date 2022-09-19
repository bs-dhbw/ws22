#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

int globalRetVal = -3; 

void *Thread1(void *vargp)
{
    printf("HelloWorld from Thread 1 \n");
    pthread_exit((void*)&globalRetVal);
}

void *Thread2(void *vargp)
{
    int localRetVal = 100;
    printf("HelloWorld from Thread 2 \n");
    return ((void*)&localRetVal);
}

int main(void)
{
    pthread_t tid1, tid2;
    int *retValT1;
    int *retValT2; 

    pthread_create(&tid1, NULL, Thread1, NULL);
    pthread_join(tid1, (void*)&retValT1);

    pthread_create(&tid2, NULL, Thread2, NULL);
    pthread_join(tid2, (void*) &retValT2);

    printf("Return value T1: %d \n", *retValT1);
    printf("Return value T2: %d \n", *retValT2);

    exit(0);
}
