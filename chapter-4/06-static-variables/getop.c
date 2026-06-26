#include "calc.h"
#include <ctype.h>
#include <stdio.h>

/* getop: get next character or numeric operand */
int getop(char s[]) {
  int i, c;
  static int bufc = '\0';

  if (bufc == '\0')
    c = getch(); // if first call just get a char
  else
    c = bufc, bufc = '\0'; // otherwise assign and reset buffer

  while ((s[0] = c) == ' ' || c == '\t')
    c = getch();

  s[1] = '\0';

  if (!isdigit(c) && c != '.')
    return c; /* not a number */

  i = 0;

  if (isdigit(c)) /* collect integer part */
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.') /* collect fraction part */
    while (isdigit(s[++i] = c = getch()))
      ;

  s[i] = '\0';

  if (c != EOF)
    bufc = c; // update buffer for next call

  return NUMBER;
}
