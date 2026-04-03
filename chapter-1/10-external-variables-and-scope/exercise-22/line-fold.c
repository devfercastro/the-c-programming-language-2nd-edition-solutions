// Exercise 1-22. Write a program to ``fold'' long input lines into two or more
// shorter lines after the last non-blank character that occurs before the n-th
// column of input. Make sure your program does something intelligent with very
// long lines, and if there are no blanks or tabs before the specified column.
#include <stdio.h>

#define MAX_LINE 1000
#define MAX_COLUMNS 10

int get_line(char[], int);
void fold_line(char[], int, char[], int);

int main(void) {
  int c;
  int len;
  char org_ln[MAX_LINE];
  char fold_ln[MAX_LINE];

  while ((len = get_line(org_ln, MAX_LINE))) {
    fold_line(org_ln, len, fold_ln, MAX_COLUMNS);
    printf("%s", fold_ln);
  }
}

int get_line(char ln[], int limit) {
  int i, c;

  i = 0;
  for (; (c = getchar()) != '\n' && c != EOF && i < limit; ++i)
    ln[i] = c;

  // Don't want it for now
  // if (c == '\n') {
  //   s[i] = '\n';
  //   ++i;
  // }

  ln[i] = '\0';

  return i;
}

void fold_line(char org_ln[], int org_ln_len, char fold_ln[], int fold_i) {
  int i, j;
  int blank_i = -1;

  i = j = 0;

  for (; i < org_ln_len; ++i, ++j) {
    fold_ln[j] = org_ln[i];

    if (org_ln[i] == ' ')
      blank_i = j;

    if (j && j % fold_i == 0) {
      if (blank_i != -1) {
        int shift = j - blank_i;
        int tmp_j = j;

        // shift forward
        while (shift) {
          int tmp = fold_ln[tmp_j];

          fold_ln[tmp_j] = fold_ln[tmp_j - 1];
          fold_ln[tmp_j + 1] = tmp;

          --tmp_j;
          --shift;
        }

        // insert fold
        fold_ln[blank_i] = '\n';

        // not sure how to explain this, but if the next fold don't have a blank
        // I need to make sure this is null so the fold logic follows the bellow
        // else branch
        blank_i = -1;
      } else {
        int tmp = fold_ln[j - 1];

        // insert fold
        fold_ln[j - 1] = '\n';

        // shift forward
        fold_ln[j + 1] = fold_ln[j];
        fold_ln[j] = tmp;
      }

      // i have moved characters one step
      ++j;
    }
  }

  fold_ln[j] = '\0';
}
