#include <chrono>
#include <vector>

#include "data_sorting.h"



static void
msort(std::vector<int> &a, int temp[], int lo, int hi,std::vector<long long> &results) {
  if (hi - lo < 2) return; //empty or single element
  int mid = (lo + hi)/2;   //select midpoint
  msort(a, temp, lo, mid,results); //mergesort lo half
  msort(a, temp, mid, hi,results); //mergesort hi half
  for (int i = lo; i < hi; ++i) {
    //copy subarray to temp
    temp[i] = a[i];
  }
  //merge temp[] subarrays back to a[]
  int i1 = lo;
  int i2 = mid;
  for (int dest = lo; dest < hi; ++dest) {
    if (i1 == mid) {
      //left sublist exhausted
      
      a[dest] = temp[i2++];
    }
    else if (i2 == hi) {
      //right sublist exhausted 
      a[dest] = temp[i1++];
    }
    else if (temp[i1] <= temp[i2]) {
      //smaller value in i1
      a[dest] = temp[i1++];
    }
    else {
      //get smaller value from i2
      a[dest] = temp[i2++];
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
    //SORT HERE

    auto finish = std::chrono::system_clock::now();
	std::chrono::duration<double> delta_time = finish - begin;
    //Time in milliseconds
    results[2] = delta_time.count() * 1000; 
    return results;
}
