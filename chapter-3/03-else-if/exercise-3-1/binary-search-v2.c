// Exercise 3-1. Our binary search makes two tests inside the loop, when one
// would suffice (at the price of more tests outside.) Write a version with only
// one test inside the loop and measure the difference in run-time.

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n) {
  int low, high, mid;

  low = 0;
  high = n - 1;
  mid = (low + high) / 2;

  // while low less than high and no match
  while (low <= high && v[mid] != x) {
    if (x < v[mid])
      high = mid + 1; // +1 to exclude middle item
    else
      low = mid + 1;

    mid = (low + high) / 2; // update mid
  }

  if (v[mid] == x) // found
    return mid;
  else
    return -1; // not found
}
