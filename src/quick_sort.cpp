#include <iostream>
#include <chrono>
#include <vector>

#include "data_sorting.h"

static void swap(std::vector<int> a, int i, int j){
  int t = a[i];
  a[i] = a[j];
  a[j] = t;
}
static int findPivot(std::vector<int> a, int i, int j){
  return (i+j)/2;
}

/** partition a [lo, hi] into < pivot left sub-array and >= pivot
 *  right sub-array, returning index of first position in right
 *  sub-array
 */
static int partition(std::vector<int> a, int lo, int hi, int pivot, std::vector<long long> results){
  std::cout << lo << std::endl;
  std::cout << hi << std::endl;
  while (lo <= hi) { //while interval is non-empty
    while (a[lo] < pivot) {
      //this loop will not run off the end of the array
      //because pivot is at a[hi]
      ++lo;
    }
     std::cout << "lo " << lo << std::endl;
    while ((hi >= lo) && (a[hi] >= pivot)) --hi;
	std::cout << "hi" << hi << std::endl; 
     results[1]++;
    if (hi > lo) swap(a, lo, hi); //swap out-of-place values
    break;
  }
  return lo;            // Return first position in right partition
}

/** sort a [lo, hi] */
static void qsort(std::vector<int> a, int lo, int hi, std::vector<long long> results){
 
  if (hi - lo < 1) return;
  int pivotindex = findPivot(a, lo, hi);  // Pick a pivot
  swap(a, pivotindex, hi);
  results[0]++;           // Stick pivot at end
  // k will be the first position in the right subarray
  
  int k = partition(a, lo, hi-1, a[hi], results);

  swap(a, k, hi);
  results[0]++;                         // Put pivot in place
  qsort(a, lo, k - 1, results);  // Sort left partition
  qsort(a, k + 1, hi, results);  // Sort right partition
  
}

/** sort a [0, n) */
std::vector<long long> quick_sort(std::vector<int> a){
  int n = a.size();
  std::vector<long long> results;
  results.resize(3);
  auto begin = std::chrono::system_clock::now();
  qsort(a, 0, n - 1, results);
  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> delta_time = finish - begin;
  //Time in milliseconds
  results[2] = delta_time.count() * 1000;
  return results;
}
