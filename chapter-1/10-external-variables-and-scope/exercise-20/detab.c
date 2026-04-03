// Exercise 1-20. Write a program detab that replaces tabs in the input with the
// proper number of blanks to space to the next tab stop. Assume a fixed set of
// tab stops, say every n columns. Should n be a variable or a symbolic
// parameter?
#include <stdio.h>

#define TAB_WIDTH 2

int main(void) {
  int c, spaces;

  while ((c = getchar()) != EOF) {
    spaces = TAB_WIDTH;
    if (c == '\t')
      while (spaces) {
        // printf("␣"); // can't see shit
        putchar(' ');
        --spaces;
      }
    else
      putchar(c);
  }
}
