// Exercise 2-5. Write the function any(s1,s2), which returns the first location
// in a string s1 where any character from the string s2 occurs, or -1 if s1
// contains no characters from s2. (The standard library function strpbrk does
// the same job but returns a pointer to the location.)
#include <stdio.h>

int any(char s1[], char s2[]);

// ai generated
void test(char *s1, char *s2, int expected) {
  int result = any(s1, s2);
  int pass = (result == expected);
  const char *status = pass ? "PASS" : "FAIL";
  const char *color = pass ? "\033[32m" : "\033[31m";
  const char *reset = "\033[0m";

  printf("s1: %-15s | s2: %-10s | Exp: %3d | Got: %3d | %s%s%s\n", s1, s2,
         expected, result, color, status, reset);
}

int main(void) {
  test("hello", "aeiou", 1);
  test("programming", "xyz", -1);
  test("abcdef", "fed", 3);
  test("hello world", " ", 5);
  test("Mississippi", "xyz", -1);
  test("Mississippi", "iS", 1);
  test("123456", "543", 2);
  test("abc123xyz", "987", -1);
  test("test@#case!", "@#!", 4);
  test("", "abc", -1);
  test("hello", "", -1);
  test("aAbBcC", "ABC", 1);
  test("repeat", "ee", 1);
  test("z", "z", 0);
  test("abc", "c", 2);

  return 0;
}

int any(char s1[], char s2[]) {
  int i, j;

  // iterate through each `s1` char
  for (i = 0; s1[i] != '\0'; ++i)
    // iterate through each `s2` char for every `s1` char
    for (j = 0; s2[j] != '\0'; ++j)
      // if chars matches return current `i` position
      if (s1[i] == s2[j])
        return i;

  return -1; // fallback no matches found
}
