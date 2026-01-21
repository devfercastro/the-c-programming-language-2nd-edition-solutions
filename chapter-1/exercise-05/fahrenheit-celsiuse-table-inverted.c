// Exercise 1-5. Modify the temperature conversion program to print the table in
// reverse order,that is, from 300 degrees to 0.

#include <stdio.h>
/* print Fahrenheit-Celsius table */
int main(void) {
  int fahr;
  printf(" F  |  C\n");
  for (fahr = 300; fahr >= 0; fahr = fahr - 20)
    printf("%3d |%6.1f\n", fahr, (5.f / 9.f) * (fahr - 32));
  return 0;
}
