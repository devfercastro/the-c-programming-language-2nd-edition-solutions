// Exercise 4-3. Given the basic framework, it's straightforward to extend the
// calculator. Add the modulus (%) operator and provisions for negative numbers.
//
// On this version I wanted to use as input arrays of chars to test it more
// easily
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

#define MAXVAL 100  /* maximum depth of val stack */
int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

// tracks the current reading position in the string
int expr_pos = 0;

int getop(char expression[], char s[]);
void push(double);
double pop(void);

double calculator(char expression[]);

void test(char expression[], double expected) {
  double result = calculator(expression);

  // performative shit seeing the current test cases
  int pass = result - expected < 0.000000001;

  const char *status = pass ? "PASS" : "FAIL";
  const char *color = pass ? "\033[32m" : "\033[31m";
  const char *reset = "\033[0m";

  printf("Expression: %20s | Exp: %20lf  Got: %20lf %s%s%s\n", expression,
         expected, result, color, status, reset);
}

int main() {
  test("1 2 - 4 5 + *", -9);
  test("1.5 2.5 - 4 5 + *", -9);
  test("1 -2 + 4 5 + *", -9);
  test("6 5 % 4 -", -3);
  test(".5 .5 + 4 -", -3);

  return 0;
}

double calculator(char expression[]) {
  int type;
  double op1, op2; // operators
  char s[MAXOP];

  sp = 0;       // reset the stack for each test case
  expr_pos = 0; // reset the string read-head for each test case

  while ((type = getop(expression, s)) != '\0') {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;

    case '+':
      push(pop() + pop());
      break;

    case '*':
      push(pop() * pop());
      break;

    case '-':
      op2 = pop();
      push(pop() - op2);
      break;

    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("error: zero divisor\n");
      break;

    case '%':
      op2 = pop();
      op1 = pop();

      if (op2 != 0.0)
        // cast to get rid of fractional part
        push(op1 - op2 * (long)(op1 / op2));
      else
        printf("error: zero divisor\n");
      break;

    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }

  // pop and return the final remaining value on the stack
  return pop();
}

/* getop: get next character or numeric operand from string */
int getop(char expression[], char s[]) {
  int c;
  int j = 0; // index for writing to s[]

  // skip whitespace using the external expr_pos
  while ((c = expression[expr_pos]) == ' ' || c == '\t')
    expr_pos++;

  s[j++] = c;
  s[j] = '\0';

  // end of string reached
  if (c == '\0') {
    return '\0';
  }

  // not a number (operator)
  if (!isdigit(c) && c != '.' && c != '-') {
    expr_pos++; // advance past the operator
    return c;
  }

  // check if '-' is an operator or is dealing with a negative number
  // this also allows insert floats in format like ".5" to atof
  if (c == '-' && !isdigit(expression[expr_pos + 1]) &&
      expression[expr_pos + 1] != '.') {
    expr_pos++; // It's just a minus operator
    return c;
  }

  // it's a number (or negative number)
  // collect integer part
  expr_pos++; // move past the first char (digit or '-') already saved in s[0]
  while (isdigit(c = expression[expr_pos])) {
    s[j++] = c;
    expr_pos++;
  }

  // collect fraction part
  if (c == '.') {
    s[j++] = c;
    expr_pos++;
    while (isdigit(c = expression[expr_pos])) {
      s[j++] = c;
      expr_pos++;
    }
  }

  s[j] = '\0'; // Terminate string for atof()
  return NUMBER;
}

/* push: push f onto value stack */
void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}
