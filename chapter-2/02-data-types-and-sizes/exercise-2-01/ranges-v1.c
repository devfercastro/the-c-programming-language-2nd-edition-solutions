// Exercise 2-1. Write a program to determine the ranges of char, short, int,
// and long variables, both signed and unsigned, by printing appropriate values
// from standard headers and by direct computation. Harder if you compute them:
// determine the ranges of the various floating-point types.
#include <float.h>
#include <limits.h>
#include <stdio.h>

int main(void) {
  // char
  printf("signed char range: (%d, %d)\n", CHAR_MIN, CHAR_MAX);
  printf("unsigned char range: (0, %d)\n", UCHAR_MAX);

  putchar('\n');

  // short
  printf("signed short range: (%d, %d)\n", SHRT_MIN, SHRT_MAX);
  printf("unsigned short range: (0, %d)\n", USHRT_MAX);

  putchar('\n');

  // int
  printf("signed int range: (%d, %d)\n", INT_MIN, INT_MAX);
  // %u has more range than %d
  printf("unsigned int range: (0, %u)\n", UINT_MAX);

  putchar('\n');

  // long
  printf("signed long range: (%lld, %lld)\n", LLONG_MIN, LLONG_MAX);
  printf("unsigned long range: (0, %llu)\n", ULLONG_MAX);

  putchar('\n');

  // float
  // `FLT_MIN` is the minimun normalized number posible with IEEE 754, same goes for double and long double
  // The %f only prints up to 6 decimal points
  printf("float range: (%e, %e)\n", -FLT_MAX, FLT_MAX);

  putchar('\n');

  // double
  printf("double range: (%e, %e)\n", -DBL_MAX, DBL_MAX);

  putchar('\n');

  // long double
  printf("long double range: (%Le, %Le)\n", -LDBL_MAX, LDBL_MAX);
}
