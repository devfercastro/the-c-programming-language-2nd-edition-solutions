// Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n
// bits that begin at position p set to the rightmost n bits of y, leaving the
// other bits unchanged.
#include <stdio.h>

// replaces n number of bits from x at position p with the n right most bits
// from y
unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y);

// AI GENERATED TESTS
void test(unsigned x, int p, int n, unsigned y, unsigned expected) {
  unsigned result = setbits(x, p, n, y);
  int pass = (result == expected);
  const char *status = pass ? "PASS" : "FAIL";
  const char *color = pass ? "\033[32m" : "\033[31m";
  const char *reset = "\033[0m";

  printf("x:%-16b p:%-2d n:%-2d y:%-10b | Exp:%-32b Got:%-32b | %s%s%s\n", x, p,
         n, y, expected, result, color, status, reset);
}

int main(void) {
  test(0b10101010, 4, 3, 0b110, 0b10111010);     // Basic replacement
  test(0b11110000, 3, 4, 0b1010, 0b11111010);    // Replace lower nibble
  test(0b1111, 4, 2, 0b11111101, 0b1111);        // y has extra bits
  test(0b0, 0, 1, 0b1, 0b1);                     // Set single bit
  test(0b10101010, 7, 8, 0b1010101, 0b1010101);  // Replace all bits
  test(0b11111111, 3, 0, 0b0, 0b11111111);       // n=0 edge case
  test(0b10101010, 4, 3, 0b10, 0b10101010);      // No change (bits match)
  test(0b0, 7, 1, 0b1, 0b10000000);              // Set MSB
  test(0b10000000, 6, 3, 0b1111111, 0b11110000); // Set 3 bits
  test(0b101010, 3, 4, 0b1111, 0b101111);        // Replacement

  return 0;
}

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y) {
  // mask with n right most bits activated
  unsigned int xmask = ~(~0U << n);
  // left shift those bits to match the position of x's target bits
  xmask = xmask << ((p + 1) - n);
  xmask = ~xmask;

  // zeroe all n target bits from x with the mask
  x = x & xmask;

  // mask with n right most bits activated to target y's bits
  unsigned int ymask = ~(~0U << n);
  y = y & ymask;          // apply mask to get only the n right most bits from y
  y = y << ((p + 1) - n); // left shift bits to match the bits from x

  x = x | y; // finally fill the target bits from x with the target bits from y

  return x;
}
