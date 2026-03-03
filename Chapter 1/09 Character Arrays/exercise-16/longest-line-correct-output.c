// Exercise 1-16. Revise the main routine of the longest-line program so it will
// correctly print the length of arbitrary long input lines, and as much as
// possible of the text.

#include <stdio.h>
#define MAXLINE 10 /* easy to test like this */

int getline_imp(char line[], int maxline);
void copy(char to[], char from[]);
void print_line_no_nl(
    char line[]); // newline chars at the end are anoying to display

/* print the longest input line */
int main(void) {
  int len;               /* current line length */
  int max;               /* maximum length seen so far */
  char line[MAXLINE];    /* current input line */
  char longest[MAXLINE]; /* longest line saved here */

  max = 0;
  while ((len = getline_imp(line, MAXLINE)) > 0) {
    if (len > max) {
      max = len;
      copy(longest, line);
    }

    printf("Length of '");
    print_line_no_nl(line);
    printf("': %d\n", len);
  }

  if (max > 0) { /* there was a line */
    printf("Longest line: '");
    print_line_no_nl(longest);
    printf("'\n");
  }

  return 0;
}

/* getline: read a line into s, return length */
int getline_imp(char s[], int lim) {
  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;

  if (c == '\n') {
    s[i] = c;
    ++i;
  }

  s[i] = '\0';

  // If program hits `lim` and line continues this will get the real length
  if (c != '\n' && c != EOF) {
    for (; (c = getchar()) != EOF && c != '\n'; ++i)
      ;
    if (c == '\n') {
      ++i;
    }
  }

  return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[]) {
  int i;
  i = 0;

  while ((to[i] = from[i]) != '\0')
    ++i;
}

void print_line_no_nl(char line[]) {
  int i;
  for (i = 0; line[i] != '\0' && line[i] != '\n'; ++i)
    putchar(line[i]);

  // Need this to differ lines that ended on newline from EOF ended
  if (line[i] == '\n') {
    putchar('\\');
    putchar('n');
  }
}
