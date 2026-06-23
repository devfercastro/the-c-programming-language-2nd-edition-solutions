// Exercise 4-1. Write the function strindex(s,t) which returns the position of
// the rightmost occurrence of t in s, or -1 if there is none.
#include <stdio.h>

int strindex(char source[], char searchfor[]);
int mstrlen(char line[]);

void test(char line[], char pattern[], int expected) {
  int result = strindex(line, pattern);

  int pass = result == expected;

  const char *status = pass ? "PASS" : "FAIL";
  const char *color = pass ? "\033[32m" : "\033[31m";
  const char *reset = "\033[0m";

  printf("Line: %-60s | %s%s%s \nExp:%d Got:%d\n", line, color, status, reset,
         expected, result);
}

/* find all lines matching pattern */
int main() {
  char pattern[] = "ould"; /* pattern to search for */

  test("Ah Love! could you and I with Fate conspire", pattern, 10);
  test("To grasp this sorry Scheme of Things entire", pattern, -1);
  test("Would not we shatter it to bits -- and then", pattern, 1);
  test("Re-mould it nearer to the Heart's Desire!", pattern, 4);
  test("Would, would idk", pattern, 8);
}

int mstrlen(char line[]) {
  int i;
  for (i = 0; line[i] != '\0'; ++i)
    ;

  return i;
}

/* strindex: return rightmost index of t in s, -1 if none */
int strindex(char s[], char t[]) {
  int i, j, k, tlen;

  // to not calculate the length of t every outter for-loop iter
  tlen = mstrlen(t);

  // start from last i position
  i = mstrlen(s) - 1;

  for (; i > 0; i--) {
    // start j from curr i pos and k from last t pos then backtrack while
    // comparing s chars with t chars until k = 0. Decrement i to end up with
    // the correct position of the pattern (if present) and decrement j and k to
    // keep comparing both s and t
    for (j = i, k = tlen - 1; k > 0 && s[j] == t[k]; j--, k--)
      ;

    // if k == 0 it means the whole pattern matches
    // otherwise the pattern is either not or barely complete in s
    if (k == 0)
      // i is at the end of the pattern matched in s
      // so substrack the length of t and add 1 to get the start position of the
      // pattern
      return (i - tlen) + 1;
  }

  return -1;
}
