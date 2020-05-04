#include <chrono>
#include <vector>

#include "data_sorting.h"



static void
msort(std::vector<int> &a, int temp[], int lo, int hi,std::vector<long long> &results) {
  if (hi - lo < 2) return; 
  int mid = (lo + hi)/2;   
  msort(a, temp, lo, mid,results); 
  msort(a, temp, mid, hi,results); 
  for (int i = lo; i < hi; ++i) {
    temp[i] = a[i];
  }
  int low = lo;
  int mi = mid;
  for (int dest = lo; dest < hi; ++dest) {
    if (low == mid) {
      a[dest] = temp[mi++];
    }
    else if (mi == hi) {
      a[dest] = temp[low++];
    }
    else if (temp[low] <= temp[mi]) {
      a[dest] = temp[low++];
    }
    else {
      a[dest] = temp[mi++];
    }
    results[1]++;
  }   
}


std::vector<long long> merge_sort(std::vector<int> data){
	//index 0 = swaps; index 1 = comparisons; index 2 = time;
    std::vector<long long> results;
    results.resize(3);
    auto begin = std::chrono::system_clock::now();
    int *temp = new int[data.size()];
    msort(data,temp,0,data.size(),results);
    delete temp;
    auto finish = std::chrono::system_clock::now();
	std::chrono::duration<double> delta_time = finish - begin;
    //Time in milliseconds
    results[2] = delta_time.count() * 1000; 
    return results;
}
