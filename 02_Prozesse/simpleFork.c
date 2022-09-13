#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    printf("Hello World...\n");

    pid_t pid = fork();

    if (pid == 0)
    {
      /* Child process */
      printf("Inside child - PID: %d\n", getpid());
    }
    else if (pid > 0)
    {
      /* Parent process */
      printf("Inside parent - PID of child process: %d\n", pid);
      printf("Inside parent - PID: %d\n", getpid());        
    }
    else
    {
      /* Error durring fork() */
      printf("fork() failed!\n");
      return EXIT_FAILURE;
    }

    printf("Bye World...\n");

    return EXIT_SUCCESS;
}
