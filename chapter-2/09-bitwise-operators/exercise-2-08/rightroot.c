// Exercise 2-8. Write a function rightrot(x,n) that returns the value of the
// integer x rotated to the right by n positions.
#include <stdio.h>

// direct calculates machine's word length
unsigned int get_word_length();

unsigned rightrot(unsigned int x, unsigned int n);

void test(unsigned x, unsigned n, unsigned expected) {
  unsigned int result = rightrot(x, n);
  int pass = (result == expected);

  const char *status = pass ? "PASS" : "FAIL";
  const char *color = pass ? "\033[32m" : "\033[31m";
  const char *reset = "\033[0m";

  printf("x:%-32b n:%-2d | Exp:%-32b Got:%-32b | %s%s%s\n", x, n, expected,
         result, color, status, reset);
}

int main(void) {
  // claude generated test cases because I'm lazy
  test(0b00000000000000000000000000001000, 2,
       0b00000000000000000000000000000010); // no wrap

  test(0b00000000000000000000000000000001, 1,
       0b10000000000000000000000000000000); // single bit wraps to MSB

  test(0b00000000000000000000000000000011, 2,
       0b11000000000000000000000000000000); // two bits wrap

  test(0b00000000000000000000000000001010, 1,
       0b00000000000000000000000000000101); // LSB=0, no wrap

  test(0b00000000000000000000000000001001, 1,
       0b10000000000000000000000000000100); // LSB=1 wraps

  test(0b11111111111111111111111111111111, 7,
       0b11111111111111111111111111111111); // all 1s unchanged

  test(0b10101010101010101010101010101010, 4,
       0b10101010101010101010101010101010); // alternating pattern stable under
                                            // 4 positions

  test(0b00000000000000000000000010101010, 4,
       0b10100000000000000000000000001010); // partial wrap

  test(0b00000000000000000000000011001100, 0,
       0b00000000000000000000000011001100); // n=0, no change

  test(0b10000000000000000000000000000000, 1,
       0b01000000000000000000000000000000); // MSB shifts right, no wrap

  test(0b01000000000000000000000000001001, 4,
       0b10010100000000000000000000000000); // idk, extra test
  
  test(0b00000000000000000000000000000101, 2,
       0b01000000000000000000000000000001); // idk, extra test
}

unsigned int get_word_length() {
  unsigned int mask = ~0U;
  int wlength;

  // right shift mask until deactivate all bits
  // increment counter each iteration
  for (wlength = 0; mask > 0; ++wlength)
    mask = mask >> 1;

  return wlength;
}

unsigned rightrot(unsigned int x, unsigned int n) {
  int wlength = get_word_length();

  // mask with all activated to save wrapped bits
  // it's initialized with it's n leftmost bits deactivated, while the rest
  // activated
  unsigned int wbits = ~0U >> n;

  unsigned int rbit = 0;

  for (; n > 0; --n) {
    rbit = x & 1; // save current right most bit
    // left shift (wlength - current n value) times, until get correct after
    // wrapp bit position
    rbit = rbit << (wlength - n);
    // save bit on wbits
    wbits = wbits | rbit;

    // rigth shift x
    x = x >> 1;
    // activate x leftmost bit
    x = x | ~(~0 >> 1); 
  }

  return wbits & x;
}
