/* trim: remove trailing blanks, tabs, newlines */
int trim(char s[]) {
  int n;

  // The for loop starts at the end and scans backwards looking for the first
  // character that is not a blank or tab or newline
  for (n = strlen(s) - 1; n >= 0; n--)
    if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
      // The loop is broken when one is found, or when n becomes negative (that
      // is, when the entire string has been scanned).
      break;

  s[n + 1] = '\0';

  return n;
}
