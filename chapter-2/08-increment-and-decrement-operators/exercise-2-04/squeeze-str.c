// Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes
// each character in s1 that matches any character in the string s2.
#include <stdio.h>
#include <string.h>

// checks if `s` contains the char `c`. If so returns it's index,
// otherwise return -1
int contains(char s[], char c);
// deletes each char in `s1` that's also in `s2`
void squeeze(char s1[], char s2[]);

// ai generated test suit
void test(char *input, char *chars_to_remove, char *expected) {
  char buffer[256];
  strncpy(buffer, input, sizeof(buffer) - 1);
  buffer[sizeof(buffer) - 1] = '\0';
  
  squeeze(buffer, chars_to_remove);
  
  int pass = strcmp(buffer, expected) == 0;
  const char *status = pass ? "PASS" : "FAIL";
  const char *color = pass ? "\033[32m" : "\033[31m";
  const char *reset = "\033[0m";
  
  printf("Input: %-15s | Remove: %-10s | Exp: %-10s | Got: %-10s | %s%s%s\n",
         input, chars_to_remove, expected, buffer, color, status, reset);
}

int main(void) {
  test("hello", "aeiou", "hll");
  test("programming", "xyz", "programming");
  test("abcdef", "ace", "bdf");
  test("aabbcc", "abc", "");
  test("hello world", " ", "helloworld");
  test("Mississippi", "is", "Mpp");
  test("123456", "246", "135");
  test("abc123xyz", "123", "abcxyz");
  test("test@#case!", "@#!", "testcase");
  test("", "abc", "");
  test("hello", "", "hello");
  test("aAbBcC", "ABC", "abc");
  test("repeat", "ee", "rpat");

  return 0;
}

int contains(char s[], char c) {
  // iterate through `s` until null
  for (int i = 0; s[i] != '\0'; ++i)
    if (s[i] == c) // break loop if `c` was found
      return i;

  return -1;
}

void squeeze(char s1[], char s2[]) {
  int i, j;

  for (i = j = 0; s1[i] != '\0'; i++)
    // every time the current `s1` char is not found on `s2`
    if (contains(s2, s1[i]) == -1)
      s1[j++] = s1[i]; // copy it to the current `j` position, and only then
                       // increment `j`

  s1[j] = '\0'; // update null `s1` char to the last `j` know position
}
