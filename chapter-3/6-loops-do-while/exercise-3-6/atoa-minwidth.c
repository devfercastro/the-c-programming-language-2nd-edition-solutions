// Exercise 3-6. Write a version of itoa that accepts three arguments instead of
// two. The third argument is a minimum field width; the converted number must
// be padded with blanks on the left if necessary to make it wide enough.
#include <limits.h>
#include <stdio.h>
#include <string.h>

// 32 bits + sign + \0
#define N 35

void reverse(char s[]);
void itoa(int n, char s[], int fw);

void test(int number, char expected[], int fw) {
  char result[N] = {0};
  itoa(number, result, fw);

  int pass = strcmp(result, expected) == 0;

  const char *status = pass ? "PASS" : "FAIL";
  const char *color = pass ? "\033[32m" : "\033[31m";
  const char *reset = "\033[0m";

  printf("Exp:%-40s Got:%-40s | %s%s%s\n", expected, result, color, status,
         reset);
}

int main() {
  // Basic padding (width > length)
  test(123, "   123", 6);
  test(-123, "  -123", 6);

  // Exact fit (width == length)
  test(123, "123", 3);
  test(-123, "-123", 4);

  // Field width smaller than number (should NOT truncate)
  test(12345, "12345", 2);
  test(-12345, "-12345", 3);

  // Edge cases
  test(0, "0", 0);
  test(0, "    0", 5);
  test(INT_MIN, "-2147483648", 5);    // Width ignored, too small
  test(INT_MIN, "  -2147483648", 13); // Padded INT_MIN
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

void itoa(int n, char s[], int fw) {
  int i, sign;
  unsigned int nn;

  sign = n;

  // cast to unsiged int to extend maximun range and convert to positive
  if (n < 0)
    // if negative, first pass to unsigned and then apply the negation
    nn = -(unsigned int)n;
  else
    nn = (unsigned int)n;

  i = 0;
  do {
    s[i++] = nn % 10 + '0';
    --fw; // decrement field width once per digit
  } while ((nn /= 10) > 0);

  if (sign < 0)
    s[i++] = '-', --fw; // add sign and decrement again field width

  // if number length < field width
  // add blanks until field width = 0
  while ((fw--) > 0)
    s[i++] = ' ';

  s[i] = '\0';

  reverse(s);
}
