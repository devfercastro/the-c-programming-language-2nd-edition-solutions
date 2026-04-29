// Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the
// rightmost 1-bit in x. Explain why. Use this observation to write a faster
// version of bitcount.
/*
 * expression `(x - 1)` deactivates the right most bit of x (x is now = x1 x2
 * ... 0), then the original x (x1 x2 ... x3) is AND with this new x, the value
 * of the AND operation is assign to x, leaving the original with it's rightmost
 * deactivated
 */
#include <stdio.h>

int bitcount(unsigned x);

void test(unsigned x, int expected) {
  int result = bitcount(x);
  int pass = (result == expected);

  const char *status = pass ? "PASS" : "FAIL";
  const char *color = pass ? "\033[32m" : "\033[31m";
  const char *reset = "\033[0m";

  printf("x:%-32b | Exp:%2d Got:%2d | %s%s%s\n", x, expected, result, color,
         status, reset);
}

int main(void) {
  test(0b00000000000000000000000000000000, 0);  // no bits set
  test(0b11111111111111111111111111111111, 32); // all bits set
  test(0b00000000000000000000000000000001, 1);  // single bit, LSB
  test(0b10000000000000000000000000000000, 1);  // single bit, MSB
  test(0b10101010101010101010101010101010,
       16); // alternating, starting from MSB
  test(0b01010101010101010101010101010101,
       16); // alternating, starting from LSB
  test(0b11110000111100001111000011110000, 16); // nibble pattern
  test(0b00000000000000000000000000001111, 4);  // lower nibble only
  test(0b11111111000000000000000000000000, 8);  // upper byte only
  test(0b00000000000000001111111111111111, 16); // lower 16 bits
}

// solution from book 'C Answer Book' (I tried)
int bitcount(unsigned x) {
  int b;

  for (b = 0; x != 0; x &= x - 1, ++b)
    ;

  return b;
}
