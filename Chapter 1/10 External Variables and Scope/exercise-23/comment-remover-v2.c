// Exercise 1-23. Write a program to remove all comments from a C program. Don't
// forget to handle quoted strings and character constants properly. C comments
// don't nest.
//
// Modified solution from "The C Answer Book" page 38
// `remove_comment` and `in_comment` functions were modified to support both
// single and multi line comments
#include <stdio.h>

void remove_comment(int);
void in_comment(int);
void echo_quote(int);

int main() {
  // Disable buffering for stdout
  // for debug purposes
  setvbuf(stdout, NULL, _IONBF, 0);

  int c;

  while ((c = getchar()) != EOF)
    remove_comment(c);
}

void remove_comment(int curr) {
  int next;

  if (curr == '/') {
    if ((next = getchar()) == '*' || next == '/')
      in_comment(next); // beginning comment
    else {
      putchar(curr); // not a comment
      putchar(next);
    }
  } else if (curr == '\'' || curr == '"')
    echo_quote(curr); // quote begin
  else
    putchar(curr); // not a comment
}

void in_comment(int type) {
  int curr, next;

  while ((curr = getchar()) != EOF) {
    // if type is '*' means multi line comment
    // check for "*/" pair and break
    if (type == '*' && curr == '*' && (next = getchar()) == '/')
      break;
    // if type is '/' means single line comment
    // check for '\n' and break
    else if (type == '/' && curr == '\n') {
      // print the newline otherwise program can brake indentation
      putchar(curr);
      break;
    }
  }
}

void echo_quote(int curr) {
  putchar(curr);

  int next;

  while ((next = getchar()) != curr) { // search for end
    putchar(next);
    if (next == '\\')
      putchar(getchar()); // ignore escape seq
  }

  putchar(next); // forgot this little bitch
}
