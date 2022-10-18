#include <stdio.h>

int main() {
  unsigned int cam[12] = {0xf83c, 0x0a93, 0xda1f, 0x093a, 0x8f1d, 0x4444,
                          0x9269, 0xc645, 0xaffe, 0x0000, 0x7e3b, 0x038a};
  _Bool valid[12] = {0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1};


  unsigned int muster, maske;

  printf("Bitte Musterwert eingeben: ");
  scanf("%i", &muster);
  printf("\nBitte Maskenwert eingeben: ");
  scanf("%i", &maske);
  printf("\n");

  printf("muster: %x   maske %x   \n", muster, maske);

/* TODO */ 

  return 0;
}
