#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
 
void *printHello(void *threadid)
{
   long tid = (long)threadid;
   printf("Hello from thread %ld, pthread ID - %lu\n", tid, pthread_self());
   return NULL;
}
 
int main(int argc, char const *argv[])
{
   pthread_t threadId;
   int rc;
   long t = 101;
   int ret;
   void *retval;
 
   rc = pthread_create(&threadId, NULL, printHello, (void *)t);
   if (rc) {
       printf("ERORR; return code from pthread_create() is %d\n", rc);
       exit(EXIT_FAILURE);
   }
 
   ret = pthread_join(threadId, &retval);
   if (retval == PTHREAD_CANCELED)
       printf("The thread was canceled - ");
   else
       printf("Returned value %d - ", (int)retval);
 
   switch (ret) {
   case 0:
       printf("The thread joined successfully\n");
       break;
   case EDEADLK:
       printf("Deadlock detected\n");
       break;
   case EINVAL:
       printf("The thread is not joinable\n");
       break;
   case ESRCH:
       printf("No thread with given ID is found\n");
       break;
   default:
       printf("Error occurred when joining the thread\n");
   }
 
   pthread_exit(NULL);
}
