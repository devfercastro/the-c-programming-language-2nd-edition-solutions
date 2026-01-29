// Exercise 1-9. Write a program to copy its input to its output, replacing each
// string of one or more blanks by a single blank.
#include <stdio.h>

int main(void) {
  int current, last = '\0';

  while ((current = getchar()) != EOF) {
    if (current == ' ' && last != ' ')
      putchar(current);
    if (current != ' ')
      putchar(current);

    last = current;
  }
}
