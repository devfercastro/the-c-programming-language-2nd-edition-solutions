// Exercise 1-8. Write a program to count blanks, tabs, and newlines.
#include <stdio.h>

int main(void) {
  int c, blanks, tabs, newlines;
  c = blanks = tabs = newlines = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ')
      ++blanks;
    if (c == '\t')
      ++tabs;
    if (c == '\n')
      ++newlines;
  }
  printf("Blanks: %d, tabs: %d, new lines: %d\n", blanks, tabs, newlines);
}
