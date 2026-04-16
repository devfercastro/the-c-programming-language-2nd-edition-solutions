/* lower: convert c to lower case; ASCII only */
int lower(int c) {
  if (c >= 'A' && c <= 'Z')
    // a much cleared way would be `return (c - 'A') + 'a'` here the
    // substraction turns to a offset (0-25) and the addition turns the result
    // of the offset into a lower case char
    // only works with ASCII because chars are secuencial here
    return c + 'a' - 'A';
  else
    return c;
}
