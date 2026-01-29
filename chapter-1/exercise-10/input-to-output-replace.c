// Exercise 1-10. Write a program to copy its input to its output, replacing
// each tab by \t, each backspace by \b, and each backslash by \\. This makes
// tabs and backspaces visible in an unambiguous way.
#include <stdio.h>
int main(void) {
  int c;
  while ((c = getchar()) != EOF) {
    if (c == '\t' || c == '\b' || c == '\\')
      putchar('\\');

    if (c == '\t')
      putchar('t');
    else if (c == '\b')
      putchar('b');
    else if (c == '\\')
      putchar('\\');
    else
      putchar(c);
  }
}
