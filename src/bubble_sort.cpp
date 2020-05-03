#include <chrono>
#include <vector>

#include "data_sorting.h"

std::vector<long long> bubble_sort(std::vector<int> a){
  //int n = a.size();
  //index 0 = swaps; index 1 = comparisons; index 2 = time;
  std::vector<long long> results;
  results.resize(3);
  auto begin = std::chrono::system_clock::now();
  for (int i = 0; i < a.size() - 1; ++i) {
    for (int j = a.size() - 1; j > i; --j) {
      results[1]++;
      if (a[j] < a[j - 1]){
          int t = a[j];
          a[j] = a[j - 1];
          a[j - 1] = t;
        results[0]++;
      }
    }
  }
  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> delta_time = finish - begin;
  //Time in milliseconds
  results[2] = delta_time.count() * 1000;
  return results;
}
