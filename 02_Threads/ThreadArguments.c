#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
/* 
 * Compile with:
 *   gcc -Wall ThreadArguments.c -lpthread
 */

typedef struct 
{
  int x;
  int y;
  int z;
} Point_Type;


void *thread_func(void *arg)
{
  Point_Type *myPointPtr = (Point_Type*) arg; 
  printf("Point[x y z]:  [%d %d %d]\n", myPointPtr->x, myPointPtr->y, myPointPtr->z);
  return(0);
}

int main(void)
{
  pthread_t threadId;

  Point_Type myPoint = {.x = 10, .y=5, .z=-3};
  pthread_create(&threadId, NULL, thread_func, &myPoint);
  
  pthread_join(threadId, NULL);

  exit(0);
}
