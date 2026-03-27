// Exercise 1-24. Write a program to check a C program for rudimentary syntax
// errors like unmatched parentheses, brackets and braces. Don't forget about
// quotes, both single and double, escape sequences, and comments. (This program
// is hard if you do it in full generality.)
#include <stdio.h>

int count_braces, count_brackets, count_parenthesis;

void matcher(int);
void in_comment(int);
void in_quote(int);

int main() {
  int curr, next;

  while ((curr = getchar()) != EOF) {
    if (curr == '/') {
      // begin comment
      if ((next = getchar()) == '/' || next == '*')
        in_comment(next);

      // not a comment
      else {
        matcher(curr);
        matcher(next); // to not miss the char that `next` swallowed
      }

    } else if (curr == '\'' || curr == '"') {
      in_quote(curr); // begin quote
    } else
      matcher(curr);
  }

  if (count_braces > 0)
    printf("Error: Missing %d enclosing '}'\n", count_braces);
  else if (count_braces < 0)
    printf("Error: Missing %d opening '{'\n", -count_braces);

  if (count_brackets > 0)
    printf("Error: Missing %d enclosing ']'\n", count_brackets);
  else if (count_brackets < 0)
    printf("Error: Missing %d opening '['\n", -count_brackets);

  if (count_parenthesis > 0)
    printf("Error: Missing %d enclosing ')'\n", count_parenthesis);
  else if (count_parenthesis < 0)
    printf("Error: Missing %d opening '('\n", -count_parenthesis);
}

void matcher(int c) {
  // braces
  if (c == '{')
    ++count_braces;
  else if (c == '}')
    --count_braces;
  // brackets
  else if (c == '[')
    ++count_brackets;
  else if (c == ']')
    --count_brackets;
  // parenthesis
  else if (c == '(')
    ++count_parenthesis;
  else if (c == ')')
    --count_parenthesis;
}

void in_comment(int comment_type) {
  int curr, next;

  curr = getchar();

  while (curr != EOF) {
    if (comment_type == '*' && curr == '*') {
      next = getchar();

      if (next == '/') // on multi line comment stop on "*/" pair
        break;

      // `next` swallowed a char, this prevent from miss it
      curr = next;
      continue; // `curr` is already updated continue

    } else if (comment_type == '/' &&
               curr == '\n') // on single comment stop on '\n'
      break;

    curr = getchar();
  }

  if (curr == EOF && comment_type == '*')
    printf("Error: Missing multiline comment enclosing\n");
}

void in_quote(int quote_type) {
  int curr;

  while ((curr = getchar()) != quote_type &&
         curr != EOF) { // keep until matching quote or EOF
    if (curr == '\\')
      getchar(); // ignore escape seq
  }

  if (curr == EOF) // end of file was reached before encounter the closing quote
    printf("Error: Missing enclosing '%c'", quote_type);
}
