#include <chrono>
#include <vector>

#include "data_sorting.h"

std::vector<int>
insertionSort(std::vector<int> data)
{

  for (int i = 1; i < data.size(); ++i) {
    //insert i'th record into sorted portion
    for (int j = i; (j > 0) && (a[j] < a[j - 1]); --j) {
      swap(data, j, j - 1);
    }
  }
  return data;
}

static void
swap(std::vector<int> vect, int i, int j)
{
  int x = vect[i];
  vect[i] = vect[j];
  vect[j] = x;
}
