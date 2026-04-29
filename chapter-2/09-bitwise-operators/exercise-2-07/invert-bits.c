// Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits
// that begin at position p inverted (i.e., 1 changed into 0 and vice versa),
// leaving the others unchanged.
#include <stdio.h>

unsigned invert(unsigned x, unsigned int p, unsigned int n);

void test(unsigned x, unsigned int p, unsigned int n, unsigned expected) {
  unsigned result = invert(x, p, n);
  int pass = (result == expected);

  // str constants
  const char *status = pass ? "PASS" : "FAIL";
  const char *color = pass ? "\033[32m"  // green if pass
                           : "\033[31m"; // red if not
  const char *reset = "\033[0m";         // restore color

  printf("x:%-16b p:%-2d n:%-2d | Exp:%-32b Got:%-32b | %s%s%s\n", x, p, n,
         expected, result, color, status, reset);
}

int main(void) {
  // claude generated test cases because I'm lazy
  test(0b011011, 3, 2, 0b010111);     // basic inversion
  test(0b00000000, 3, 4, 0b00001111); // all zeros inverted
  test(0b11111111, 7, 1, 0b01111111); // invert MSB
  test(0b11111111, 0, 1, 0b11111110); // invert LSB
  test(0b10000001, 6, 6, 0b11111111); // invert zeros in middle
  test(0b11111111, 6, 6, 0b10000001); // invert ones in middle
  test(0b10110100, 5, 3, 0b10001100); // invert mixed middle bits
  test(0b01010101, 4, 5, 0b01001010); // invert alternating lower bits
  test(0b00001111, 7, 4, 0b11111111); // invert zero upper nibble
  test(0b11110000, 7, 4, 0b00000000); // invert one upper nibble
  test(0b10101010, 7, 8, 0b01010101); // invert all bits
}

unsigned invert(unsigned int x, unsigned int p, unsigned int n) {
  // mask with it's n rightmost bits activated, leftshift to match the position
  // of the n bits on x, AND it with x to save the n target bits and then
  // invert them
  unsigned mask = ~(~0U << n);
  mask = mask << ((p + 1) - n);
  mask = x & mask;
  mask = ~mask;

  // same as before but this time x it's OR with this secondary mask to activate
  // all n target bits at position p
  unsigned smask = ~(~0U << n);
  smask = smask << ((p + 1) - n);
  x = x | smask;

  // finally AND x with the first mask to replace all n activated on x with the
  // ones saved on the mask
  x = x & mask;

  return x;
}
