// Exercise 1-13. Write a program to print a histogram of the lengths of words
// in its input. It is easy to draw the histogram with the bars horizontal; a
// vertical orientation is more challenging.
#include <stdio.h>
#define IN 1
#define OUT 0
#define MAX_WORD_LENGTH 20

int main(void) {
  int lengths_arr[MAX_WORD_LENGTH] = {0};
  int c, state, word_length;

  word_length = 0;
  state = OUT;
  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
      if (state == IN) {
        state = OUT;
        lengths_arr[word_length - 1]++; // Fucking zero indexing
        word_length = 0;
      }
    } else {
      state = IN;
      word_length++;
    }
  }

  // If input finishes on a word the above while loop will not execute the logic
  // to update `lenghts_arr`
  if (state == IN && word_length >= 0 && word_length <= MAX_WORD_LENGTH) {
    lengths_arr[word_length - 1]++; // Fucking zero indexing again
  }

  printf("\nHORIZONTAL HISTOGRAM:\n");
  printf("Lengths | Count\n");
  for (int i = 0; i < MAX_WORD_LENGTH; i++) {
    printf("  %2d    | ", i + 1);
    for (int j = 0; j < lengths_arr[i]; j++) {
      printf("*");
    }
    printf("\n");
  }

  printf("\nVERTICAL HISTOGRAM:\n* y-axis word count and x-axis lengths\n");
  int max_lengths_arr_item = 0;
  for (int i = 0; i < MAX_WORD_LENGTH; i++) {
    int current_length_arr_item = lengths_arr[i];
    if (current_length_arr_item > max_lengths_arr_item)
      max_lengths_arr_item = current_length_arr_item;
  }

  int columns = MAX_WORD_LENGTH;
  int rows = max_lengths_arr_item;

  for (int i = rows; i > 0; i--) {
    for (int j = 0; j < columns; j++) {
      int current_length_arr_item = lengths_arr[j];
      if (j == 0)
        printf("%2d |", i);
      if (current_length_arr_item >= i)
        printf(" * ");
      else
        printf("   ");
    }
    printf("\n");
  }

  printf("    ");
  for (int i = 0; i < columns; i++) {
    printf("---");
  }
  printf("\n    ");
  for (int i = 0; i < columns; i++) {
    printf("%2d ", i + 1);
  }
}
