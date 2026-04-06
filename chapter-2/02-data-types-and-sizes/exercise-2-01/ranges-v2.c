// Exercise 2-1. Write a program to determine the ranges of char, short, int,
// and long variables, both signed and unsigned, by printing appropriate values
// from standard headers and by direct computation. Harder if you compute them:
// determine the ranges of the various floating-point types.
#include <stdio.h>

// asuming the platform uses two's complement for char, short, int and long
// and size of char < short < int < long
unsigned char uc_max;
unsigned short us_max;
unsigned int ui_max;
unsigned long ul_max;

float f_max;

void char_range();
void short_range();
void int_range();
void long_range();
void float_range();
void double_range();
void long_double_range();

int main(void) {
  char_range();
  putchar('\n');
  short_range();
  putchar('\n');
  int_range();
  putchar('\n');
  long_range();
  putchar('\n');
  float_range();
  putchar('\n');
  double_range();
  putchar('\n');
  long_double_range();
}

void char_range() {
  unsigned char next = 1;

  // double `next` until wrapps to 0
  for (; next != 0; next *= 2)
    uc_max = next;

  // if char size = 8 bit then uc = 128 after for-loop
  signed char sc_min = -uc_max;
  signed char sc_max = uc_max - 1;

  uc_max = uc_max + (uc_max - 1);
  us_max = uc_max + 1; // start unsigned short from `uc_max` to save iterations

  printf("signed char range: (%d, %d)\n", sc_min, sc_max);
  printf("unsigned char range: (0, %u)\n", uc_max);
}

void short_range() {
  unsigned short next = us_max;

  for (; next != 0; next *= 2)
    us_max = next;

  signed short ss_min = -us_max;
  signed short ss_max = us_max - 1;

  us_max = us_max + (us_max - 1);
  ui_max = us_max + 1;

  printf("signed short range: (%d, %d)\n", ss_min, ss_max);
  printf("unsigned short range: (0, %u)\n", us_max);
}

void int_range() {
  unsigned int next = ui_max;

  for (; next != 0; next *= 2)
    ui_max = next;

  signed int si_min = -ui_max;
  signed int si_max = ui_max - 1;

  ui_max = ui_max + (ui_max - 1);
  // I kinda don't get why I have to cast `ui_max` only here and not on the past
  // functions but basically if I don't, `ui_max` wrapps to 0 screwing things
  // for `long_range`
  ul_max = (long)ui_max + 1;

  printf("signed int range: (%d, %d)\n", si_min, si_max);
  printf("unsigned int range: (0, %u)\n", ui_max);
}

void long_range() {
  unsigned long next = ul_max;

  for (; next != 0; next *= 2)
    ul_max = next;

  signed long sl_min = -ul_max;
  signed long sl_max = ul_max - 1;

  ul_max = ul_max + (ul_max - 1);

  printf("signed long range: (%ld, %ld)\n", sl_min, sl_max);
  printf("unsigned long range: (0, %lu)\n", ul_max);
}

void float_range() {
  float last_finite, curr, next;

  last_finite = curr = 0;
  next = 1;

  // calculate biggest finite power of two until inf < inf
  while (curr < next) {
    last_finite = curr;

    curr = next;
    next *= 2;
  }

  curr = last_finite;
  float increment = last_finite / 2;
  next = last_finite + increment;

  // backfill the lower precision bits by adding last power's halfe, quarter, on
  // eight, etc. until inf < inf
  while (curr < next) {
    last_finite = curr;

    curr = next;

    increment /= 2;
    next = next + increment;
  }

  printf("float range: (%e, %e)\n", -last_finite, last_finite);
}

void double_range() {
  double last_finite, curr, next;

  last_finite = curr = 0;
  next = 1;

  // calculate biggest finite power of two until inf < inf
  while (curr < next) {
    last_finite = curr;

    curr = next;
    next *= 2;
  }

  curr = last_finite;
  double increment = last_finite / 2;
  next = last_finite + increment;

  // backfill the lower precision bits by adding last power's halfe, quarter, on
  // eight, etc. until inf < inf
  while (curr < next) {
    last_finite = curr;

    curr = next;

    increment /= 2;
    next = next + increment;
  }

  printf("double range: (%e, %e)\n", -last_finite, last_finite);
}

void long_double_range() {
  long double last_finite, curr, next;

  last_finite = curr = 0;
  next = 1;

  // calculate biggest finite power of two until inf < inf
  while (curr < next) {
    last_finite = curr;

    curr = next;
    next *= 2;
  }

  curr = last_finite;
  long double increment = last_finite / 2;
  next = last_finite + increment;

  // backfill the lower precision bits by adding last power's halfe, quarter, on
  // eight, etc. until inf < inf
  while (curr < next) {
    last_finite = curr;

    curr = next;

    increment /= 2;
    next = next + increment;
  }

  printf("long double range: (%Le, %Le)\n", -last_finite, last_finite);
}
