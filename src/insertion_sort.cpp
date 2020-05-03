#include <chrono>
#include <vector>
#include <iostream>

#include "data_sorting.h"




std::vector<long long>
insertion_sort(std::vector<int> data)
{
   std::vector<long long> results;
   results.resize(3);
   auto begin = std::chrono::system_clock::now();
  for (int i = 1; i < data.size(); ++i) {
    //insert i'th record into sorted portion
    for (int j = i; (j > 0) && (data[j] < data[j - 1]); --j) {
      
      int x = data[j];
      data[i] = data[j-1];
      data[j-1] = x;
	  results[0]++;
	  results[1]++;
    }
  }
  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> delta_time = finish - begin;
  //Time in milliseconds
  results[2] = delta_time.count() * 1000;
  return results;
}

