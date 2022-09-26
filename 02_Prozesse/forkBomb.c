#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

  while (1) {
    fork();
  }
}
