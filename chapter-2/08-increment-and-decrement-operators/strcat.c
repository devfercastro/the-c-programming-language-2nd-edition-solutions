/* strcat: concatenate t to end of s; s must be big enough */
void strcat(char s[], char t[]) {
  int i, j;

  i = j = 0;
  while (s[i] != '\0') /* find end of s */
    i++;

  // As each member is copied from t to s, the postfix ++ is applied to both i
  // and j to make sure that they are in position for the next pass through the
  // loop.
  while ((s[i++] = t[j++]) != '\0') /* copy t */
    ;
}
