// Exercise 3-3. Write a function expand(s1,s2) that expands shorthand
// notations like a-z in the string s1 into the equivalent complete list
// abc...xyz in s2. Allow for letters of either case and digits, and be
// prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a
// leading or trailing - is taken literally.
//
// Solution based on book C Answer Book
// Book's solution is way cooler
#include <stdio.h>
#include <string.h>

void expand(char s1[], char s2[]);

// ai generated tests
void test(char *description, char *input, char *expected) {
  char result[256] = {0};
  expand(input, result);
  int pass = strcmp(result, expected) == 0;

  const char *status = pass ? "PASS" : "FAIL";
  const char *color = pass ? "\033[32m" : "\033[31m";
  const char *reset = "\033[0m";

  printf("%-40s | Exp:%-40s Got:%-40s | %s%s%s\n", description, expected,
         result, color, status, reset);
}

int main(void) {
  test("empty string", "", "");
  test("no ranges", "abc", "abc");
  test("full lowercase", "a-z", "abcdefghijklmnopqrstuvwxyz");
  test("full uppercase", "A-Z", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  test("full digits", "0-9", "0123456789");
  test("partial lowercase", "a-e", "abcde");
  test("partial uppercase", "A-E", "ABCDE");
  test("partial digits", "0-4", "01234");
  test("lowercase and digits", "a-z0-9",
       "abcdefghijklmnopqrstuvwxyz0123456789");
  test("uppercase and digits", "A-Z0-9",
       "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
  test("leading dash literal", "-a-z", "-abcdefghijklmnopqrstuvwxyz");
  test("trailing dash literal", "a-z-", "abcdefghijklmnopqrstuvwxyz-");
  test("both dashes literal", "-a-z-", "-abcdefghijklmnopqrstuvwxyz-");
  test("same char range a-a", "a-a", "a");
  test("text mixed with range", "0a-z9", "0abcdefghijklmnopqrstuvwxyz9");
}

void expand(char s1[], char s2[]) {
  int i, j; // i and j are to keep track of s1 and s2
  // are meant to save the left, middle and right character of a secuence. i.e:
  // a-z l = a, m = -, r = z
  char l, m, r;

  i = j = 0;
  while ((l = s1[i++]) != '\0') { // get the left char
    m = s1[i];                    // get the middle char

    // if middle is the special char, and right is equal/bigger than left
    if (m == '-' && s1[i + 1] >= l) {
      r = s1[++i]; // get right char

      while (l < r) // expand secuence until left equal right
        s2[j++] = l++;

    } else // middle is not the special char, just save left
      s2[j++] = l;
  }

  s2[j] = '\0';
}
