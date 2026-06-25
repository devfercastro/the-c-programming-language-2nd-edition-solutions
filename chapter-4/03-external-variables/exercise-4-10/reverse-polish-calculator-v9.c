// Exercise 4-10. An alternate organization uses getline to read an entire input
// line; this makes getch and ungetch unnecessary. Revise the calculator to use
// this approach.
//
// solution made with book "C Answer Book"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <string.h>

#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define PCM '1'    // possible command or math function

#define MAXVAL 100  /* maximum depth of val stack */
int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

// there will never be more than one character
// used as fallback to save an ungeted char
int bufc = '\0';

// to save answer (ANS) that's also the last printed op
// initialized as 0 just for a compiler warning
double ans_val = 0;

char iline[MAXOP] = {0}; // input line
int ilp = 0;             // next free iline[] position

int getop(char[]);

void push(double);
double pop(void);

void matchs(char s[]);

int mygetline(char s[]);

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

    case PCM: // a possible one plus letter or a math function
      matchs(s);
      break;

    case '=': // assing a variable
      pop();  // remove dummy letter so the next pop() get the value to assign

      if (var >= 'A' && var <= 'Z')
        // get the value and save it in corresponding letter position
        vars[var - 'A'] = pop();
      else
        printf("error: no variable found\n");
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

  // file doesn't end with newline and stack is not empty
  if (sp > 0)
    printf("\t%.8g\n", pop());

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

  // if ilinep points to null means it's first line or prev line was proccesed
  if (iline[ilp] == '\0') {
    if (mygetline(iline) == 0) // assign line
      return EOF;
    else
      ilp = 0; // new line assigned reset input line pointer
  }

  // skip banks until find a candidate
  while ((s[0] = c = iline[ilp++]) == ' ' || c == '\t')
    ;

  s[1] = '\0'; // the rest on s doesn't matter

  i = 0;

  // possible command or math function
  if (isalpha(c)) {
    // save the entire string on s[]
    while (1) {
      int next = iline[ilp++];

      // if next is valid save it on s[]
      if (isalpha(next))
        s[++i] = next;
      // otherwise move back a position to not loose it
      else {
        ilp--;
        break;
      }
    }

    s[i + 1] = '\0';

    // i == 0 possible one letter command, otherwise possible plus one letter
    // command or math function
    return i > 0 ? PCM : c;
  }

  if (!isdigit(c) && c != '.' && c != '-')
    return c; /* not a number */

  // check if '-' is not being used for a negative number
  if (c == '-' && !isdigit(s[++i] = c = iline[ilp++])) {
    if (c != EOF) // ignore EOF
      ilp--;      // to not miss the char after the sign
    return s[0];
  }

  if (isdigit(c) || c == '-') /* collect integer part */
    while (isdigit(s[++i] = c = iline[ilp++]))
      ;
  if (c == '.') /* collect fraction part */
    while (isdigit(s[++i] = c = iline[ilp++]))
      ;

  s[i] = '\0'; // discard the char after the number

  if (c != EOF)
    ilp--; // to not miss the input line char after the number

  return NUMBER;
}

// check s[] for command (more than one letter command) or math function
void matchs(char s[]) {
  double op2;

  // math functions
  if (strcmp(s, "sin") == 0)
    push(sin(pop()));
  else if (strcmp(s, "exp") == 0)
    push(exp(pop()));
  else if (strcmp(s, "pow") == 0)
    op2 = pop(), push(pow(pop(), op2));

  // commands
  // for now the only command with more than one letter
  else if (strcmp(s, "ANS") == 0)
    push(ans_val);

  else
    printf("error: unknown expression %s\n", s);
}

// getline from input and return it's length
int mygetline(char s[]) {
  int c, i = 0;

  // save chars while i is < MAXOP or newline/EOF is encounter
  for (; i < MAXOP && (s[i] = c = getchar()) != '\n' && c != EOF; i++)
    ;

  // end fucking line after last char
  // do not remove the newline or EOF char that's gonna be handle else where
  // FUUUUUUUUUUUUUUUUUUUUUUUCK
  s[i + 1] = '\0';

  return i;
}
