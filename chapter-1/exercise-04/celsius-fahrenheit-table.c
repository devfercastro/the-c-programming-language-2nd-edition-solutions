// Exercise 1-4. Write a program to print the corresponding Celsius to
// Fahrenheit table.

#include <stdio.h>
/* print Fahrenheit-Celsius table
for fahr = 0, 20, ..., 300; floating-point version */
int main() {
  float fahr, celsius;
  int lower, upper, step;
  lower = 0;   /* lower limit of temperatuire scale */
  upper = 300; /* upper limit */
  step = 20;   /* step size */
  celsius = lower;
  printf(" C  |  F\n");
  while (celsius <= upper) {
    fahr = celsius * (9.f / 5.f) + 32.f;
    printf("%3.0f |%6.1f\n", celsius, fahr);
    celsius += step;
  }
}
