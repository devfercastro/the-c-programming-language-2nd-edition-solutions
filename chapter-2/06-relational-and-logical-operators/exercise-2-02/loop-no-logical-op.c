// Exercise 2-2. Write a loop equivalent to the for loop above without using &&
// or ||.
#include <stdio.h>

int main() {
  int lim = 10;
  int i, c;

  char s[lim];

  // for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
  //   s[i] = c;

  for (i = 0; i < lim - 1; ++i) {
    c = getchar();

    if (c == '\n')
      break;
    if (c == EOF)
      break;

    s[i] = c;
  }
}
