#include <chrono>
#include <vector>

#include "data_sorting.h"

std::vector<long long> merge_sort(std::vector<int> data){
	//index 0 = swaps; index 1 = comparisons; index 2 = time;
    std::vector<long long> results;
    results.resize(3);
    auto begin = std::chrono::system_clock::now();

    //SORT HERE

    auto finish = std::chrono::system_clock::now();
	std::chrono::duration<double> delta_time = finish - begin;
    //Time in milliseconds
    results[2] = delta_time.count() * 1000; 
    return results;
}
