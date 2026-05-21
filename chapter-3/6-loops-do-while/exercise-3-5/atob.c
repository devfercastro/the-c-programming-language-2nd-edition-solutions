// Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into
// a base b character representation in the string s. In particular,
// itob(n,s,16) formats s as a hexadecimal integer in s.
#include <limits.h>
#include <stdio.h>
#include <string.h>

// 32 bits + sign + \0
#define N 35

void reverse(char s[]);
void itob(int n, char s[], int b);

void test(int number, int base, char expected[]) {
  char result[N] = {0};
  itob(number, result, base);

  int pass = strcmp(result, expected) == 0;

  const char *status = pass ? "PASS" : "FAIL";
  const char *color = pass ? "\033[32m" : "\033[31m";
  const char *reset = "\033[0m";

  printf("Exp:%-40s Got:%-40s | %s%s%s\n", expected, result, color, status,
         reset);
}

int main() {
  // Base 10 (Decimal)
  test(INT_MIN, 10, "-2147483648");
  test(-5, 10, "-5");
  test(INT_MAX, 10, "2147483647");
  test(5, 10, "5");

  // Base 2 (Binary)
  test(5, 2, "101");
  test(-5, 2, "-101");
  test(255, 2, "11111111");

  // Base 8 (Octal)
  test(8, 8, "10");
  test(64, 8, "100");
  test(255, 8, "377");

  // Base 16 (Hexadecimal)
  test(255, 16, "FF");
  test(4096, 16, "1000");
  test(INT_MAX, 16, "7FFFFFFF");
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

void itob(int n, char s[], int b) {
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
    int rest = nn % b;

    if (rest < 10)
      s[i++] = rest + '0';
    else
      // if remaider >=10 means hexa
      // - 10 to get an offset from 0 to 5
      // + 'A' to get an offset from A to F
      s[i++] = (rest - 10) + 'A';

  } while ((nn /= b) > -1);

  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';

  reverse(s);
}
