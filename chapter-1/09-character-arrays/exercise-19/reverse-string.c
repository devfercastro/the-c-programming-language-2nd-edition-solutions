// Exercise 1-19. Write a function reverse(s) that reverses the character string
// s. Use it to write a program that reverses its input a line at a time.
#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int getline_imp(char line[], int maxline);
void reverse_string(char line[], int len);

/* print the longest input line */
int main(void) {
  int len;            /* current line length */
  char line[MAXLINE]; /* current input line */

  while ((len = getline_imp(line, MAXLINE)) > 0) {
    printf("Original: '%s'\n", line);
    reverse_string(line, len);
    printf("Reversed: '%s'\n\n", line);
  }

  return 0;
}

/* getline: read a line into s, return length */
int getline_imp(char s[], int lim) {
  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;

  // I don't want this
  // if (c == '\n') {
  //   s[i] = c;
  //   ++i;
  // }

  s[i] = '\0';

  return i;
}

void reverse_string(char line[], int len) {
  int mid = (int)(len / 2);
  int tmp;

  for (int i = 0; i < mid; ++i) {
    tmp = line[i];
    line[i] = line[len - 1 - i];
    line[len - 1 - i] = tmp;
  }
}
