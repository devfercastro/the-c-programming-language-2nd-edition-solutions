/* squeeze: delete all c from s */
void squeeze(char s[], int c) {
  int i, j;

  for (i = j = 0; s[i] != '\0'; i++)
    if (s[i] != c)
      // Each time a non-c occurs, it is copied into the current j position, and
      // only then is j incremented to be ready for the next character.
      // Equivalent to
      // ```
      // s[j] = s[i];
      // j++;
      // ```
      s[j++] = s[i];
  s[j] = '\0';
}
