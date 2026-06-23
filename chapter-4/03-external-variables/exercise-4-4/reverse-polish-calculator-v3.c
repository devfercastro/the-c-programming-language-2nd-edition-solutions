// Exercise 4-4. Add the commands to print the top elements of the stack without
// popping, to duplicate it, and to swap the top two elements. Add a command to
// clear the stack.
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

#define MAXVAL 100  /* maximum depth of val stack */
int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getop(char[]);

void push(double);
double pop(void);

int getch(void);
void ungetch(int);

/* reverse Polish calculator */
int main() {
  int type;
  double op2, op1;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
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

    case '\n':
      printf("\t%.8g\n", pop());
      break;

    case 'p': // print top elements
      if (sp > 0)
        printf("stack top: %lf\n", val[sp - 1]);
      else
        printf("error: stack empty\n");
      break;

    case 'd': // duplicate op
      op2 = pop();
      push(op2), push(op2);
      break;

    case 's': // swap ops
      op2 = pop();
      op1 = pop();
      push(op2), push(op1);
      break;

    case 'c': // clear stack
      while (sp > 0)
        pop();
      break;

    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }

  return 0;
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

/* getop: get next character or numeric operand */
int getop(char s[]) {
  int i, c;

  // skip banks until find a candidate
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;

  s[1] = '\0'; // the rest on s doesn't matter

  if (!isdigit(c) && c != '.' && c != '-')
    return c; /* not a number */

  i = 0;

  // check if '-' is not being used for a negative number
  if (c == '-' && !isdigit(s[++i] = c = getch())) {
    if (c != EOF)
      ungetch(c); // to not miss the char after the sign
    return s[0];
  }

  if (isdigit(c) || c == '-') /* collect integer part */
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.') /* collect fraction part */
    while (isdigit(s[++i] = c = getch()))
      ;

  s[i] = '\0'; // discard the char after the number

  if (c != EOF)
    ungetch(c); // to not miss the char after the number

  return NUMBER;
}

/* get a (possibly pushed-back) character */
int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

/* push character back on input */
void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
