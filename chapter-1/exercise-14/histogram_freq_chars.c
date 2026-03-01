#include <stdio.h>

#define BUFFER 200

int main(void) {
  int char_count[BUFFER] = {0};
  int c = 0;

  while ((c = getchar()) != EOF) {
    ++char_count[c];
  }

  for (int row = 0; row <= BUFFER; ++row) {
    int current_count = char_count[row];

    // Skip characters with zero aparitions
    if (current_count == 0)
      continue;

    printf("%c |", row);
    for (int column = 0; column < current_count; ++column) {
      printf("*");
    }
    printf("\n");
  }
}
