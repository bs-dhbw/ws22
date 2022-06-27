#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("PROGRAMMSTART\n");

    int counter = 0;
    pid_t pid = fork();

    if (pid == 0)
    {
        // Hier befinden wir uns im Kindprozess
        int i = 0;
        for (; i < 4; ++i)
        {
            printf("            PID: %d; ", getpid());
            printf("Kindprozess: counter=%d\n", ++counter);
        }
    }
    else if (pid > 0)
    {
        // Hier befinden wir uns im Elternprozess
        
	printf("pid of child: %d\n",pid);

	int j = 0;
        for (; j < 4; ++j)
        {
            printf("PID: %d; ", getpid());
            printf("Elternprozess: counter=%d\n", ++counter);
        }
    }
    else
    {
        // Fehler bei fork()
        printf("fork() fehlgeschlagen!\n");
        return 1;
    }

    printf("PROGRAMMENDE\n");

    return 0;
}
