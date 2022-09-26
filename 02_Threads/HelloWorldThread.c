#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *ThreadHello( void *arg) {
    printf("Hello");
    pthread_exit(0);
}

void *ThreadWorld( void *arg) {
    printf("World\n");
    pthread_exit(0);
}

int main (void) 
{
    pthread_t ThreadIdHello;
    pthread_t ThreadIdWorld; 
    
    /* Fire up Hello thread and wait until complete */ 
    pthread_create(&ThreadIdHello, NULL, ThreadHello, NULL);
    pthread_join(ThreadIdHello, NULL);

    /* Fire up World thread and wait until complete */ 
    pthread_create(&ThreadIdWorld, NULL, ThreadWorld, NULL);
    pthread_join(ThreadIdWorld, NULL);

    exit(0);
}