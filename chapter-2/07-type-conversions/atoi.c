/* atoi: convert s to integer */
int atoi(char s[]) {
  int i, n;

  n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
    // awesome way to append a digit after another
    // moves the previous digit to the left by multiplying it by 10 forming a
    // new number, the current digit is then added to that number
    n = 10 * n + (s[i] - '0');

  return n;
}
