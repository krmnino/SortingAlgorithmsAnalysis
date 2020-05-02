
swap(int a[], int i, int j)
{
  int t = a[i];
  a[i] = a[j];
  a[j] = t;
}
static int findPivot(int a[], int i, int j)
{
  return (i+j)/2;
}

/** partition a [lo, hi] into < pivot left sub-array and >= pivot
 *  right sub-array, returning index of first position in right
 *  sub-array
 */
static int partition(int a[], int lo, int hi, int pivot)
{
  while (lo <= hi) { //while interval is non-empty
    while (a[lo] < pivot) {
      //this loop will not run off the end of the array
      //because pivot is at a[hi]
      ++lo;
    }
    while ((hi >= lo) && (a[hi] >= pivot)) --hi;
    if (hi > lo) swap(a, lo, hi); //swap out-of-place values
  }
  return lo;            // Return first position in right partition
}

/** sort a [lo, hi] */
static void qsort(int a[], int lo, int hi)
{
  if (hi - lo < 1) return;
  int pivotindex = findPivot(a, lo, hi);  // Pick a pivot
  swap(a, pivotindex, hi);           // Stick pivot at end
  // k will be the first position in the right subarray
  int k = partition(a, lo, hi-1, a[hi]);
  swap(a, k, hi);                        // Put pivot in place
  qsort(a, lo, k - 1);  // Sort left partition
  qsort(a, k + 1, hi);  // Sort right partition
}

/** sort a [0, n) */
void quickSort(int a[], int n)
{
  qsort(a, 0, n - 1);
}
