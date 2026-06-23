#include <ctype.h>
/* atof: convert string s to double */
double atof(char s[]) {
  double val, power;
  int i, sign;

  for (i = 0; isspace(s[i]); i++) /* skip white space */
    ;

  // get sign and move i one position
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;

  // append all digits in order before the '.'
  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');

  // if '.' move i one position and continue appending in order
  if (s[i] == '.')
    i++;
  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10; // needed to know how many digits the fractional part has
  }

  // add the sign then using power get the fractional part
  return sign * val / power;
}
