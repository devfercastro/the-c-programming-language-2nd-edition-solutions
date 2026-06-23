// Exercise 4-2. Extend atof to handle scientific notation of the form
// 123.45e-6
// where a floating-point number may be followed by e or E and an optionally
// signed exponent.
#include <ctype.h>
#include <stdio.h>

double atofe_exp(char s[], int i);
double atofe(char s[]);

void test(char input[], double expected) {
  double result = atofe(input);

  int pass = result == expected;

  const char *status = pass ? "PASS" : "FAIL";
  const char *color = pass ? "\033[32m" : "\033[31m";
  const char *reset = "\033[0m";

  printf("Input: %10s | Exp: %20lf  Got: %20lf %s%s%s\n", input, expected,
         result, color, status, reset);
}

int main() {
  test("123.45e-6", -0.00012345);
  test("123.45e+6", 123450000);
  test("123.45e6", 123450000);
}

// exp: iterate s from position i to get an exponent
double atofe_exp(char s[], int i) {
  int acc;
  double exponent = 1;

  // on minus sign, negate exp and move one position
  if (s[i] == '-')
    exponent = -1, i++;
  // on plus sign just move on position exp is already
  // positive
  else if (s[i] == '+')
    i++;

  // basically string to int to get number of iter for the exponent
  for (acc = 0; isdigit(s[i]); i++)
    acc = 10 * acc + (s[i] - '0');

  // get the actual exponent
  while (acc--)
    exponent *= 10;

  return exponent;
}

/* atof: convert string s to double */
double atofe(char s[]) {
  double val, power, exp;
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
  val = sign * val / power;

  // exponent for scientific notation,
  // by default is positive making + sign optional
  exp = 1;

  // check if exponent indicator is present
  if (s[i] == 'e' || s[i] == 'E') {
    i++;                   // move past the indicator
    exp = atofe_exp(s, i); // get exponent
  }

  // if negative move digits to right otherwise move digits to left
  return exp < 0 ? val / exp : val * exp;
}
