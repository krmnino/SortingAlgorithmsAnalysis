#include <chrono>
#include <vector>

#include "data_sorting.h"

std::vector<long long> selection_sort(std::vector<int> data){
    //index 0 = swaps; index 1 = comparisons; index 2 = time;
    std::vector<long long> results;
    results.resize(3);
    auto begin = std::chrono::system_clock::now();
    //Selection sort
    for (int i = 0; i < data.size(); i++){
        int min_index = i;
        for (int j = data.size() - 1; j > i; j--){
            results[1]++;
            if (data[j] < data[min_index]){
                min_index = j;
            }
        }
        results[0]++;
        int temp = data[i];
        data[i] = data[min_index];
        data[min_index] = temp;
    }
    auto finish = std::chrono::system_clock::now();
	std::chrono::duration<double> delta_time = finish - begin;
    //Time in milliseconds
    results[2] = delta_time.count() * 1000; 
    return results;
}
