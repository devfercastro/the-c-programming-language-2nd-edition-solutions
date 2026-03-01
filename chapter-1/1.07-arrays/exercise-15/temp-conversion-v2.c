// Exercise 1.15. Rewrite the temperature conversion program of Section 1.2 to
// use a function for conversion.
#include <stdio.h>

float fahr_to_cel(float fahr);

/* print Fahrenheit-Celsius table
for fahr = 0, 20, ..., 300; floating-point version */
int main() {
  float fahr, celsius;
  float lower, upper, step;
  lower = 0;   /* lower limit of temperatuire scale */
  upper = 300; /* upper limit */
  step = 20;   /* step size */
  fahr = lower;
  printf(" F  |  C\n");
  while (fahr <= upper) {
    // celsius = (5.0 / 9.0) * (fahr - 32.0);
    celsius = fahr_to_cel(fahr);
    printf("%3.0f |%6.1f\n", fahr, celsius);
    fahr = fahr + step;
  }
}

float fahr_to_cel(float fahr) { return (5.0 / 9.0) * (fahr - 32.0); }
