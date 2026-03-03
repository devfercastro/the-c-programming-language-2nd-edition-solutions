// Exercise 1-18. Write a program to remove trailing blanks and tabs from each
// line of input, and to delete entirely blank lines.

#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int getline_imp(char line[], int maxline);
void print_whites(char line[]);

/* print the longest input line */
int main(void) {
  int len;            /* current line length */
  char line[MAXLINE]; /* current input line */

  while ((len = getline_imp(line, MAXLINE)) > 0)
    print_whites(line);

  return 0;
}

/* getline: read a line into s, return length minus any number of trainling
 * whites*/
int getline_imp(char s[], int lim) {
  int c, i;
  int skip_count;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
    if (c == ' ' || c == '\t')
      ++skip_count;
    else
      skip_count = 0;

    s[i] = c;
  }

  // reverse `i` to the last non blank char
  if (skip_count > 0)
    i -= skip_count;

  if (c == '\n') {
    s[i] = c;
    ++i;
  }

  s[i] = '\0';

  return i;
}

// So whites are more visible on console
void print_whites(char line[]) {
  int i = 0;
  for (; line[i] != '\0'; ++i) {
    if (line[i] == ' ')
      printf("\\_");
    else if (line[i] == '\t')
      printf("\\t");
    else
      putchar(line[i]);
  }
}
