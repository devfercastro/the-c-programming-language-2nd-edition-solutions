#include <ctype.h>

/*
 * skip white space, if any
 * get sign, if any
 * get integer part and convert it
 *
 * atoi: convert s to integer; version 2 */
int atoi(char s[]) {
  int i, n, sign;

  for (i = 0; isspace(s[i]); i++)
    ;

  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;

  for (n = 0; isdigit(s[i]); i++)
    n = 10 * n + (s[i] - '0');

  return sign * n;
}
