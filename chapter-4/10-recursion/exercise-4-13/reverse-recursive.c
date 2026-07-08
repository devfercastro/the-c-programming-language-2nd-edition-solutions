// Exercise 4-13. Write a recursive version of the function reverse(s), which
// reverses the string s in place.
#include <stdio.h>
#include <string.h>
// Solution based on book "C Answer Book"

void reverse(char s[]) {
  void reverser(char s[], int left, int right);

  reverser(s, 0, strlen(s) - 1);
}

void reverser(char s[], int left, int right) {
  char tmp;

  if (left >= right)
    return;

  tmp = s[left];

  s[left] = s[right];
  s[right] = tmp;

  reverser(s, left + 1, right - 1);
}

void test(char input[], char expected[]) {
  printf("input: %10s | ", input);
  reverse(input);

  int pass = strcmp(input, expected) == 0 ? 1 : 0;

  printf("expected: %10s | result: %10s | %5s\n", expected, input,
         pass ? "PASS" : "FAIL");
}

int main() {
  char input[] = "test";
  char expected[] = "tset";
  test(input, expected);
}
