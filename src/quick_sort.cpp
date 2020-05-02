#include <iostream>
#include <chrono>
#include <vector>

#include "data_sorting.h"
static int findPivot(std::vector<int>& a, int i, int j){
  return (i+j)/2;
}

/** partition a [lo, hi] into < pivot left sub-array and >= pivot
 *  right sub-array, returning index of first position in right
 *  sub-array
 */
static int partition(std::vector<int>& a, int lo, int hi, std::vector<long long>& results){
	int pivot = a[hi];	
	int i = (lo - 1); // Index of smaller element  
  
    for (int j = lo; j <= hi - 1; j++)  
    {  
        // If current element is smaller than the pivot  
		results[1]++;
        if (a[j] < pivot)  
        {  
            i++; // increment index of smaller element  
			int t = a[i];  
    		a[i] = a[j];  
    		a[j] = t;
			results[0]++; 
        }  
    }  
 
	int t = a[i + 1];  
    a[i + 1] = a[hi];  
    a[hi] = t;
	results[0]++;
    return (i + 1);    
	
}

/** sort a [lo, hi] */
static void qsort(std::vector<int>& a, int lo, int hi, std::vector<long long>& results){
  if (lo < hi)  
    {  
        /* pi is partitioning index, arr[p] is now  
        at right place */
        int pi = partition(a, lo, hi, results);  
  
        // Separately sort elements before  
        // partition and after partition  
        qsort(a, lo, pi - 1, results);  
        qsort(a, pi + 1, hi, results);  
    }  
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
  n = sizeof(a) / sizeof(a[0]);  
  std::cout << "Sorted array: \n";  
  for (int i = 0; i < a.size(); i++)  
  std::cout << a[i] << " ";  
  std::cout << std::endl;  
  return results;
}
