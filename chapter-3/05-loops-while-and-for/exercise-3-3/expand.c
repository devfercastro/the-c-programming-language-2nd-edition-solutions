// Exercise 3-3. Write a function expand(s1,s2) that expands shorthand
// notations like a-z in the string s1 into the equivalent complete list
// abc...xyz in s2. Allow for letters of either case and digits, and be
// prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a
// leading or trailing - is taken literally.
//
// Cases like a-9 or 0-z will break the code but I don't care, so...
#include <stdio.h>
#include <string.h>

int cType(char c);
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

int isValid(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
         (c >= '0' && c <= '9');
}

void expand(char s1[], char s2[]) {
  int i, j, p, c, n;

  for (i = 0, j = 0; s1[i] != '\0'; ++i, ++j) {
    c = s1[i];

    if (c == '-') { // possible expand
      // get prev and next
      p = s1[i - 1];
      n = s1[i + 1];

      // first or last char is '-' save it on s2 and continue
      if (!p || !n) {
        s2[j] = c;
        continue;
      }

      // check if both are valid
      if (isValid(p) && isValid(n)) {
        int start = p + 1, // +1 because prev is already saved
            end = n;

        for (; start <= end; ++start, ++j) { // expand
          s2[j] = start;
        }

        --j; // remove the for's extra j's increment (outter loop will do it)
        ++i; // to skip next char on following iter

      } else // if not save all on s2
        s2[j] = p, s2[++j] = c, s2[++j] = n;

    } else // not an expand, just save the char on s2
      s2[j] = c;
  }

  s2[j] = '\0';
}
