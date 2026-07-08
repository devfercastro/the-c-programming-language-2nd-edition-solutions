// Exercise 4-12. Adapt the ideas of printd to write a recursive version of
// itoa; that is, convert an integer into a string by calling a recursive
// routine.
#include <stdio.h>
#include <string.h>

#define L 10 // max string lenght

void atoa(int n, char s[]) {
  // keep record of i between recursive calls
  // normal calls doesn't matter it always set i to zero after the number has no
  // more digits
  static int i;

  // delete a digit from right and call again
  if (n / 10)
    atoa(n / 10, s);

  // no more digits, set i to zero and add a minus sign if number is positive
  else {
    i = 0;
    if (n < 0)
      s[i++] = '-';
  }

  // after all that, n always must be positive
  if (n < 0)
    n = -n;

  // add the digit
  s[i++] = n % 10 + '0';
}

void test(int n, char expected[]) {
  char result[L] = {0};
  atoa(n, result);

  int pass = strcmp(result, expected) == 0 ? 1 : 0;

  printf("input: %10d | expected: %10s | result: %10s | %5s\n", n, expected, result,
         pass ? "PASS" : "FAIL");
}

int main() {
  test(110, "110");
  test(-110, "-110");
  test(22, "22");
  test(-22, "-22");
}
