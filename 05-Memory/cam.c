/* Vorlagedatei zu E1 Aufgabe 6 (Speicherverwaltung) */
/* 17.06.05/gle */

#include <stdio.h>

int main() {
  unsigned int cam[12] = {0xf83c, 0x0a93, 0xda1f, 0x093a, 0x8f1d, 0x4444,
                          0x9269, 0xc645, 0xaffe, 0x0000, 0x7e3b, 0x038a};
  _Bool valid[12] = {0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1};

  unsigned short cam2[10] = {0xd2, 0xf1, 0xed, 0x53, 0xa2,
                             0x79, 0x14, 0xde, 0x03, 0xd5};
  _Bool valid2[10] = {1, 1, 0, 1, 1, 1, 1, 0, 1, 1};
  unsigned int muster, maske;

  printf("Bitte Musterwert eingeben: ");
  scanf("%i", &muster);
  printf("\nBitte Maskenwert eingeben: ");
  scanf("%i", &maske);
  printf("\n");

  printf("muster: %x   maske %x   \n", muster, maske);

  for (unsigned int i = 0; i < 10; i++) {
    if (valid2[i] == 1) {
      if ((muster & maske) == (cam2[i] & maske)) {
        printf("Hit bei %d", i);
        printf("cam: %x ", cam2[i]);
      }
    }
  }

  return 0;
}