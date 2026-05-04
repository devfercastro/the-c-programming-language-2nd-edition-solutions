/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1]
 *
 * Binary search first compares the input value x to the middle element of the
 * array v. If x is less than the middle value, searching focuses on the lower
 * half of the table, otherwise on the upper half. In either case, the next step
 * is to compare x to the middle element of the selected half.
 *
 */
int binsearch(int x, int v[], int n) {
  int low, high, mid;

  low = 0;
  high = n - 1;

  while (low <= high) {
    mid = (low + high) / 2;

    if (x < v[mid])
      high = mid + 1; // +1 excludes the middle item

    else if (x > v[mid])
      low = mid + 1;

    else /* found match */
      return mid;
  }

  return -1; /* no match */
}
