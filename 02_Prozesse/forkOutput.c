#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
 
void forkOutput()
{
   int x = 1;
 
   if (fork() == 0)
       printf("Child has x = %d\n", ++x);
   else
       printf("Parent has x = %d\n", --x);
}
int main()
{
   forkOutput();
   return 0;
}
