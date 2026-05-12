
/*
 * The following function is a Shell sort for sorting an array of integers. The
 * basic idea of this sorting algorithm, which was invented in 1959 by D. L.
 * Shell, is that in early stages, far-apart elements are compared, rather than
 * adjacent ones as in simpler interchange sorts. This tends to eliminate large
 * amounts of disorder quickly, so later stages have less work to do. The
 * interval between compared elements is gradually decreased to one, at which
 * point the sort effectively becomes an adjacent interchange method.
 *
 * shellsort: sort v[0]...v[n-1] into increasing order */
void shellsort(int v[], int n) {
  int gap, i, j, temp;

  /* There are three nested loops. */

  /* The outermost controls the gap between compared elements, shrinking it from
   * n/2 by a factor of two each pass until it becomes zero. */
  for (gap = n / 2; gap > 0; gap /= 2)
    /* The middle loop steps along the elements. */
    for (i = gap; i < n; i++)
      /* The innermost loop compares each pair of elements that is separated by
       * gap and reverses any that are out of order. */
      for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
        temp = v[j];
        v[j] = v[j + gap];
        v[j + gap] = temp;
      }
  /* Since gap is eventually reduced to one, all elements are eventually
   * ordered correctly. */
}
