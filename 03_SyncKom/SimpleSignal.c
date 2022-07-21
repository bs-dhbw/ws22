#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void catcher(int sigtype)
{
  printf("Received signal: %d\n", sigtype);
}

int main()
{
  signal(SIGINT, catcher);
  
  printf("Own PID: %d\n", getpid());

  for (int i = 1; i < 100; i++)
  {
    printf("Working...\n");
    sleep(1);
  }
}