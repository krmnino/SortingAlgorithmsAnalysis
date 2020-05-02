#include <chrono>
#include <vector>

#include "data_sorting.h"


static void
swap(std::vector<int> vect, int i, int j)
{
	int x = vect[i];
	vect[i] = vect[j];
	vect[j] = x;
}

std::vector<long long>
insertion_sort(std::vector<int> data)
{
	std::vector<long long> results;
	results.resize(3);
  for (int i = 1; i < data.size(); ++i) {
    //insert i'th record into sorted portion
    for (int j = i; (j > 0) && (data[j] < data[j - 1]); --j) {
      swap(data, j, j - 1);
	  results[0]++;
	  results[1]++;
    }
  }
  return results;
}

