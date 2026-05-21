// Exercise 3-4. In a two's complement number representation, our version of
// itoa does not handle the largest negative number, that is, the value of n
// equal to -(2wordsize-1). Explain why not. Modify it to print that value
// correctly, regardless of the machine on which it runs.
#include <limits.h>
#include <stdio.h>
#include <string.h>

// 10 digits plus sign
#define N 11

void reverse(char s[]);
void itoa(int n, char s[]);
void itoa_fix(int n, char s[]);

void test(int input, char expected[]) {
  char result[N] = {0};
  itoa_fix(input, result);

  int pass = strcmp(result, expected) == 0;

  const char *status = pass ? "PASS" : "FAIL";
  const char *color = pass ? "\033[32m" : "\033[31m";
  const char *reset = "\033[0m";

  printf("Exp:%-40s Got:%-40s | %s%s%s\n", expected, result, color, status,
         reset);
}

int main() {
  test(INT_MIN, "-2147483648");
  test(-5, "-5");
  test(5, "5");
}

void reverse(char s[]) {
  int i, length = 0;

  for (i = 0, length = 0; s[i] != '\0'; ++i, ++length) // get length of s
    ;

  // reverse s
  for (i = 0; i < length / 2; ++i) {
    char tmp = s[i];
    s[i] = s[length - 1 - i];
    s[length - 1 - i] = tmp;
  }
}

/* itoa: convert n to characters in s */
// doesn't work largest negative number -(2^(word_size - 1))
void itoa(int n, char s[]) {
  int i, sign;

  if ((sign = n) < 0)
    // this will cause overflow on signed int, n will stay as a negative number
    n = -n;

  i = 0;
  do {
    // `n % 10` always returns negative so the offset `+ '0'` never works
    s[i++] = n % 10 + '0';

    // loop will stop after one iteration because n is still negative failing
    // loop's condition
  } while ((n /= 10) > 0);

  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';

  reverse(s);
}

void itoa_fix(int n, char s[]) {
  int i, sign;

  unsigned int nn;

  // cast to unsiged int to extend maximun range and convert to positive
  if (n < 0)
    // if negative, first pass to unsigned and then apply the negation
    nn = -(unsigned int)n;
  else
    nn = (unsigned int)n;

  sign = n;

  i = 0;
  do {
    s[i++] = nn % 10 + '0';
  } while ((nn /= 10) > 0);

  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';

  reverse(s);
}
