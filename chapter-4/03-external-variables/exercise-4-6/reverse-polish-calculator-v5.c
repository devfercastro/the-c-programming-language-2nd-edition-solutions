// Exercise 4-6. Add commands for handling variables. (It's easy to provide
// twenty-six variables with single-letter names.) Add a variable for the most
// recently printed value.
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

#define SIN '1'
#define EXP '2'
#define POW '3'

#define ANS '4'

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

int smatch(char s[], char ptrn[]);

/* reverse Polish calculator */
int main() {
  int type;
  // mean to hold the past value of type
  // target are possible variable letters
  int var = 0;
  double op2, op1;
  char s[MAXOP] = {0};

  // to save values of variables from 'A' to 'Z'
  double vars[26] = {0};
  // to save answer (ANS) that's also the last printed op
  // initialized as 0 just for a compiler warning
  double ans_val = 0;

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

    case '\n':         // print solution after newline char
      ans_val = pop(); // ANS is the result of the last line
      printf("\t%.8g\n", ans_val);
      break;

    case 'p': // print top elements
      if (sp > 0) {
        printf("stack top: %lf\n", val[sp - 1]);
        ans_val = val[sp - 1]; // ANS can also be the top of the stack
      } else
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

    // math functions
    case SIN:
      push(sin(pop()));
      break;
    case EXP:
      push(exp(pop()));
      break;
    case POW:
      op2 = pop();
      op1 = pop();
      push(pow(op1, op2));
      break;

    case '=': // assing a variable
      pop();  // remove dummy letter so the next pop() get the value to assign

      if (var >= 'A' && var <= 'Z')
        // get the value and save it in corresponding letter position
        vars[var - 'A'] = pop();
      else
        printf("error: no variable found\n");
      break;
    case ANS: // push ANS to the stack
      push(ans_val);
      break;

    default:
      if (type >= 'A' && type <= 'Z') // dealing with a variable
        push(vars[type - 'A']);       // get the var value and use it
      else
        printf("error: unknown command %s\n", s);
      break;
    }

    // keep track of the prev value of type for the next iter
    var = type;
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

  i = 0;

  // check if dealing with a math function
  if (c == 'e' && smatch(s, "exp"))
    return EXP;
  if (c == 's' && smatch(s, "sin"))
    return SIN;
  if (c == 'p' && smatch(s, "pow"))
    return POW;

  // command
  if (c == 'A' && smatch(s, "ANS"))
    return ANS;

  if (!isdigit(c) && c != '.' && c != '-')
    return c; /* not a number */

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

// check if s[] completely matches ptrn[]
// return 1 if so, otherwise 0
int smatch(char s[], char ptrn[]) {
  int i = 0;

  // compare while saving chars on s[]
  while (ptrn[i] != '\0' && s[i] == ptrn[i])
    s[++i] = getch();

  // if i is not pointing to the end of ptrn[]
  // means they don't match
  if (ptrn[i] != '\0') {
    // save the chars on buf
    while (i)
      ungetch(s[i--]);

    return 0;
  }

  // last iter on main while loop gets an extra char for s[]
  // this prevent loosing it
  ungetch(s[i]);

  s[i] = '\0'; // update end of s[]

  return 1;
}
