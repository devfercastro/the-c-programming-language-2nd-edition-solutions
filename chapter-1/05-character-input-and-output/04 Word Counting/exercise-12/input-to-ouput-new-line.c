#include <stdio.h>
#define IN 1
#define OUT 0

int main(void) {
  int c, state;

  state = OUT;
  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
      if (state == IN) { // Only prints a new line after RECENTLY exit a word
        state = OUT;
        putchar('\n');
      }
    } else { // Inside a word
      state = IN;
      putchar(c);
    }
  }
}
