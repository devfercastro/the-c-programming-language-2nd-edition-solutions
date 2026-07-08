/* qsort: sort v[left]...v[right] into incresing order */
// left and right params on first call are usually set to the first and last
// position
void qsort(int v[], int left, int right) {
  int i, last;
  void swap(int v[], int i, int j);

  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */

  // the pivot is the mid elem moved to the start of v[]
  swap(v, left, (left + right) / 2); /* move partition elem */
  last = left;                       /* to v[0] */

  // move all elems smaller than pivot behind it
  // keep track of all small elems with the help of last
  for (i = left + 1; i <= right; i++) /* partition */
    if (v[i] < v[left])
      swap(v, ++last, i);

  // using last now pivot is moved past all the smaller elems that were
  // positioned behind it.
  // leaving pivot between it's smallest and bigest elems in v[]
  swap(v, left, last); /* restore partition elem */

  // call again on the part before the pivot
  qsort(v, left, last - 1);
  // call again on the part after the pivot
  qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j) {
  int temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
