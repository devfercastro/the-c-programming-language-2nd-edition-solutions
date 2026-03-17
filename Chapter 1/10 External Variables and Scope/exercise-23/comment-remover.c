#include <stdio.h>

#define DEFAULT 0 // outside a block

#define IN_SG_COMM 1 // inside single line comment block
#define IN_ML_COMM 2 // inside multi line comment block
#define IN_STR 3     // inside string block
#define IN_CHAR 4    // inside char block

#define M_SIMP 0 // to move `curr` to `next` (one simple step)
#define M_DOUB 1 // to move `curr` two steps

#define P_NONE 0 // to print nothing
#define P_SIMP 1 // to print only `curr`
#define P_DOUB 2 // to print `curr` and `next

int main() {
  // Disable buffering for stdout
  // for debug purposes
  setvbuf(stdout, NULL, _IONBF, 0);

  // holds the current character
  int curr,
      // holds the next one
      next,
      // flag to decide if print nothing, `curr` char or both `curr` and `next`
      // char
      print,
      // flag to decide how to move `curr`, one or two steps
      move,
      // indicates the state of the program to check if is/not inside a some
      // block (commen, string, etc)
      state;

  // start program by asumming it's not inside a block
  state = DEFAULT;
  curr = getchar();

  while (curr != EOF) {
    // use to decide how to move `curr`
    // by default move simple (one step)
    move = M_SIMP;

    // by default print nothing otherwise change it
    print = P_NONE;

    next = getchar();

    if (state == DEFAULT) {
      if (curr == '/' && next == '/') { // if // enter single line
        state = IN_SG_COMM;
        move = M_DOUB; // move double to continue from the first char inside the
                       // comment block
      } else if (curr == '/' && next == '*') { // if /* enter multi line
        state = IN_ML_COMM;
        move = M_DOUB; // move double to continue from the first char inside the
                       // comment block
      } else if (curr == '"') { // if " enter string
        print = P_SIMP;         // to print the first "
        state = IN_STR;
      } else if (curr == '\'') { // if ' enter char
        print = P_SIMP;          // to print the first '
        state = IN_CHAR;
      } else
        print = P_SIMP; // to just print the char normally

    } else if (state == IN_SG_COMM) {
      // look for \n to exit single line
      if (curr == '\n') {
        // need to print the newline otherwise if it will append current line's
        // blanks with following line's blanks (if both have) breaking
        // indentation
        print = P_SIMP;

        state = DEFAULT;
      }

    } else if (state == IN_ML_COMM) {
      // look for */ to exit multi line
      if (curr == '*' && next == '/') {
        move =
            M_DOUB; // move double to continue with chars outside block comment
        state = DEFAULT;
      }

    } else if (state == IN_STR) {
      print = P_SIMP; // simple print inside a string block

      // if scaped double quote print both, move `curr` two steps
      if (curr == '\\' && next == '"') {
        print = P_DOUB;
        move = M_DOUB;
      }
      // else if " restore state to default
      else if (curr == '"')
        state = DEFAULT;

    } else if (state == IN_CHAR) {
      print = P_SIMP; // simple print inside a string block

      if (curr == '\\' && next == '\\') {
        print = P_DOUB;
        move = M_DOUB;
      } else if (curr == '\\' && next == '\'') {
        print = P_DOUB;
        move = M_DOUB;
      }
      // look for ' to exit char
      else if (curr == '\'')
        state = DEFAULT;
    }

    // control flow to print
    if (print == P_SIMP)
      putchar(curr);
    else if (print == P_DOUB) {
      putchar(curr);
      putchar(next);
    }

    // control flow to update `curr`
    if (move)
      curr = getchar();
    else
      curr = next;
  }
}
