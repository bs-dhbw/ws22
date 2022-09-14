#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
    
    char *args[]={"./exec",NULL};
       
    printf("Hello from %s\n", __FILE__);

    execvp(args[0],args);
     
    printf("Goodbye from %s\n", __FILE__);
     
    return 0;
}
