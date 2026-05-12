// Exercise 3-2. Write a function escape(s,t) that converts characters like
// newline and tab into visible escape sequences like \n and \t as it copies the
// string t to s. Use a switch. Write a function for the other direction as
// well, converting escape sequences into the real characters.
#include <stdio.h>
#include <string.h>

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

// ai generated tests
void test_escape(char *description, char *input, char *expected) {
  char result[256] = {0};
  escape(input, result);
  int pass = strcmp(result, expected) == 0;

  const char *status = pass ? "PASS" : "FAIL";
  const char *color = pass ? "\033[32m" : "\033[31m";
  const char *reset = "\033[0m";

  printf("%-40s | Exp:%-20s Got:%-20s | %s%s%s\n", description, expected,
         result, color, status, reset);
}

void test_unescape(char *description, char *input, char *expected) {
  char result[256] = {0};
  unescape(input, result);
  int pass = strcmp(result, expected) == 0;

  const char *status = pass ? "PASS" : "FAIL";
  const char *color = pass ? "\033[32m" : "\033[31m";
  const char *reset = "\033[0m";

  printf("%-40s | input: %-20s | %s%s%s\n", description, input, color, status,
         reset);
}

int main(void) {
  printf("--- escape ---\n");
  test_escape("empty string", "", "");
  test_escape("no special chars", "hello", "hello");
  test_escape("newline only", "\n", "\\n");
  test_escape("tab only", "\t", "\\t");
  test_escape("newline and tab", "\n\t", "\\n\\t");
  test_escape("text around newline", "a\nb", "a\\nb");
  test_escape("text around tab", "a\tb", "a\\tb");
  test_escape("multiple special chars", "a\tb\nc", "a\\tb\\nc");
  test_escape("special chars at edges", "\thello\n", "\\thello\\n");

  printf("\n--- unescape ---\n");
  test_unescape("empty string", "", "");
  test_unescape("no escape sequences", "hello", "hello");
  test_unescape("newline sequence", "\\n", "\n");
  test_unescape("tab sequence", "\\t", "\t");
  test_unescape("newline and tab", "\\n\\t", "\n\t");
  test_unescape("text around newline", "a\\nb", "a\nb");
  test_unescape("text around tab", "a\\tb", "a\tb");
  test_unescape("multiple sequences", "a\\tb\\nc", "a\tb\nc");
  test_unescape("sequences at edges", "\\thello\\n", "\thello\n");
}

void escape(char s[], char t[]) {
  int i, j;

  for (i = 0, j = 0; s[i] != '\0'; ++i, ++j) {
    int c = s[i];

    if (c == '\n' || c == '\t') { // target secuences
      t[j] = '\\';

      switch (c) {
      case '\n':
        t[++j] = 'n';
        break;
      case '\t':
        t[++j] = 't';
        break;
      default:
        break;
      }

    } else // normal character
      t[j] = c;
  }
}

void unescape(char s[], char t[]) {
  int i, j;

  for (i = 0, j = 0; s[i] != '\0'; ++i, ++j) {
    int c = s[i];

    if (c == '\\') { // may be the start of a secuence
      int n = s[++i];

      // based on next char confirm if is a newline, a tab or just
      // normals chars
      switch (n) {
      case 'n':
        t[j] = '\n';
        break;
      case 't':
        t[j] = '\t';
        break;
      default: // definetly not a secuence, save both on t
        t[j] = c;
        t[++j] = n;
        break;
      }

    } else // definetly not a secuence
      t[j] = c;
  }
}
