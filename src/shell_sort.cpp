#include <chrono>
#include <vector>
#include <cmath>

#include "data_sorting.h"

std::vector<long long> shell_sort(std::vector<int> data){
    //index 0 = swaps; index 1 = comparisons; index 2 = time;
    std::vector<long long> results;
    results.resize(3);
    //Create set of gaps for the Shell sort to use 
    int h = 0;
    while(pow(2, h)-1 < data.size()){
        ++h;
    }
    std::vector<int> gaps;
    for(int i = 0; i < h-1; i++){
        gaps.push_back(pow(2, h - 1 - i) - 1);
    }
    //Shell sort begin
    int swaps = 0;
    int comparisons = 0;
    int time = 0;
    auto begin = std::chrono::system_clock::now();
    for(int i = 0; i < gaps.size(); i++){
        for(int j = gaps[i]; j < data.size(); j++){
            int temp = data[j];
            int k = j;
            while(k >= gaps[i] && data[k - gaps[i]] > temp){
                results[0]++;
                results[1]++;
                data[k] = data[k - gaps[i]];
                data[k-gaps[i]] = temp;
                k -= gaps[i];
            }
        }
    }
    auto finish = std::chrono::system_clock::now();
	std::chrono::duration<double> delta_time = finish - begin;
    //Time in milliseconds
    results[2] = delta_time.count() * 1000; 
    return results;

}