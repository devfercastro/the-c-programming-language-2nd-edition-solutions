/* bitcount: count 1 bits in x */
// Declaring the argument x to be an unsigned ensures that when it is
// right-shifted, vacated bits will be filled with zeros, not sign bits,
// regardless of the machine the program is run on.
int bitcount(unsigned x) {
  int b;

  for (b = 0; x != 0; x >>= 1)
    // checks if the right most is active, if so count it
    if (x & 01)
      b++;

  return b;
}
