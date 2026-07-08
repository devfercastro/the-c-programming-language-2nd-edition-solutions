#include <stdio.h>

/* printd: print n in decimal */
void printd(int n) {
  // handle negative numbers
  if (n < 0) {
    putchar('-');
    n = -n;
  }

  // call again with n minus one right digit
  if (n / 10)
    printd(n / 10);

  // will print in correct order
  putchar(n % 10 + '0');
}

int main() { printd(12340); }
