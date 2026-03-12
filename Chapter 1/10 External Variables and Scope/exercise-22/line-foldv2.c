// Exercise 1-22. Write a program to ``fold'' long input lines into two or more
// shorter lines after the last non-blank character that occurs before the n-th
// column of input. Make sure your program does something intelligent with very
// long lines, and if there are no blanks or tabs before the specified column.
#include <stdio.h>

#define MAX_COLUMNS 10
#define TAB_WIDTH 8

char line[MAX_COLUMNS]; // circular dependency

int inc_i(int, int); // to correctly update the line index
void print_line(int, int);
void exp_tab(int, int);

int main(void) {

  int c;

  int col = 0;
  int i = 0;

  int blank_col = -1;

  int spaces_left = 0;

  while ((c = getchar()) != EOF) {
    // Flush buffer after a newline, and reset all column and last blank
    // indicator
    if (c == '\n') {
      if (col > 0)
        print_line(inc_i(i, -col + MAX_COLUMNS), col);

      // reset the column and last blank position indicators
      col = 0;
      blank_col = -1;

      // the rest of the logic will bug the program
      continue;
    }

    if (c == '\t') {
      // there's no room to expand the tab, sooo add as many spaces and print
      // the line
      if (TAB_WIDTH + col > MAX_COLUMNS) {
        int spaces = MAX_COLUMNS - col;

        exp_tab(i, spaces);

        // increment i and print line
        i = inc_i(i, spaces);
        print_line(i, col + spaces);

        // next line must start as a fresh one
        col = 0;
      }
      // there's room to expand the full size of a tab
      else {
        int spaces = TAB_WIDTH;

        exp_tab(i, spaces);

        i = inc_i(i, spaces);
        col += spaces;

        // last space is a fold candidate
        blank_col = col;
      }

      // the rest of the logic will bug the program so skip it
      continue;
    }

    line[i] = c;

    // `line` is meant as a circular array
    i = inc_i(i, 1);
    ++col;

    if (c == ' ')
      blank_col = col;

    if (!(col < MAX_COLUMNS)) {
      // to make sure it prints until last blank, if no blank was found print
      // until last column
      int col_stop = blank_col != -1 ? blank_col : col;

      print_line(inc_i(i, col), col_stop);

      // if a blank was found it's important to not loose track of leftover
      // chars after the blank
      col = blank_col != -1 ? col - blank_col : 0;
      blank_col = -1;
    }
  }

  // forgot last chars
  if (col > 0)
    print_line(inc_i(i, -col + MAX_COLUMNS), col);
}

int inc_i(int i, int inc) { return (i + inc) % MAX_COLUMNS; }

void print_line(int i, int col_stop) {
  for (; col_stop; i = inc_i(i, 1), --col_stop) {
    putchar(line[i]);
  }

  putchar('\n');
}

void exp_tab(int i, int spaces) {
  for (; spaces; i = inc_i(i, 1), --spaces) {
    line[i] = ' ';
  }
}
