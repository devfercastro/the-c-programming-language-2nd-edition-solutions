// Exercsise 1-6. Verify that the expression getchar() != EOF is 0 or 1.
#include <stdio.h>

int main(void) {
  printf("Expression value %d\n", getchar() != EOF); // On linux press Ctrl+D to send EOF to the program
  return 0;
}
