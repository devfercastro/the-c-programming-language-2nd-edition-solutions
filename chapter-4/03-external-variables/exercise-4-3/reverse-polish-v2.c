// Exercise 4-3. Given the basic framework, it's straightforward to extend the
// calculator. Add the modulus (%) operator and provisions for negative numbers.
#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int getop(char[]);
void push(double);
double pop(void);

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

    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }

  return 0;
}

////////////////////////////////////////////////////////////////

#define MAXVAL 100  /* maximum depth of val stack */
int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

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

////////////////////////////////////////////////////////////////

#include <ctype.h>

int getch(void);
void ungetch(int);

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

  // if is not dealing with a negative number return the sign
  // predecrement i so in case the condition fails i is already pointing to the
  // next position in s
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

////////////////////////////////////////////////////////////////

#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

/* get a (possibly pushed-back) character */
int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

/* push character back on input */
void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
