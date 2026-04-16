// Exercise 2-3. Write a function htoi(s), which converts a string of
// hexadecimal digits (including an optional 0x or 0X) into its equivalent
// integer value. The allowable digits are 0 through 9, a through f, and A
// through F.
#include <stdio.h>

/* lower: convert c to lower case; ASCII only */
int lower(int c) {
  if (c >= 'A' && c <= 'Z')
    return c + 'a' - 'A';
  else
    return c;
}

// checks if a char is and valid hexa, case insensitive
int valid_hex(char c);

// convert hexa symbol to decimal representation
int hex_s_to_dec(char c);

// convert an hexadecimal string into integer
int htoi(char s[]);

void test(char *input, int expected) {
  int result = htoi(input);
  printf("Input: %-10s | Exp: %11d | Got: %11d | %s\n", input, expected, result,
         result == expected ? "PASS" : "FAIL");
}

int main(void) {
  test("0", 0);
  test("1", 1);
  test("f", 15);
  test("F", 15);
  test("0x1A", 26);
  test("0Xff", 255);
  test("abcDEF", 11259375);
  test("0x0007", 7);
  test("7FFFFFFF", 2147483647);
  test("100", 256);

  return 0;
}

int valid_hex(char c) {
  return (c >= '0' && c <= '9') || (lower(c) >= 'a' && lower(c) <= 'f');
}

int hex_s_to_dec(char c) {
  int n = 0;         // just to avoid a compiler warning
  int lc = lower(c); // make sure everything is lower case

  if (c >= '0' && c <= '9')
    n = c - '0';
  else if (lc >= 'a' && lc <= 'f')
    n = (lc - 'a') + 10;

  return n;
}

int htoi(char s[]) {
  int i, n;
  i = n = 0;

  // skips the optional "0x" or "0X"
  if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X'))
    i += 2;

  for (; valid_hex(s[i]); ++i) {
    n = (16 * n) + hex_s_to_dec(s[i]);
  }

  return n;
}
