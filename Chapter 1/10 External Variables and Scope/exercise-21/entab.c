// Exercise 1-21. Write a program entab that replaces strings of blanks by the
// minimum number of tabs and blanks to achieve the same spacing. Use the same
// tab stops as for detab. When either a tab or a single blank would suffice to
// reach a tab stop, which should be given preference?
#include <stdio.h>

#define TAB_WIDTH 2 // number of spaces per tab

int main(void) {
  int c, spaces;

  while ((c = getchar()) != EOF) {
    spaces = TAB_WIDTH;

    if (c == ' ') {
      for (; (c = getchar()) == ' ' && spaces; --spaces)
        ;

      printf("\\t"); // can't see shit
      // putchar('\t');
    } else
      putchar(c);
  }
}
