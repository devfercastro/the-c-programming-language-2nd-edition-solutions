#include <stdio.h>

int my_pow(int, int);
void char_range();

int main(void) { char_range(); }

int my_pow(int base, int exp) {
  int n;

  for (n = 1; exp; --exp)
    n *= base;

  return n;
}

void char_range() {
  int min, max;

  signed char c = 1;
  int base = 0;

  while (c != 0) {
    if (c < 0) { // change of sign (wrapp around)
      min = c;   // get min

      for (; c < 0; --c) // go backguards until positive
        ;
      max = c; // get max
    }

    // binary increment
    c = my_pow(2, base);
    ++base;
  }

  printf("signed char range (%d, %d)\n", min, max);
}
