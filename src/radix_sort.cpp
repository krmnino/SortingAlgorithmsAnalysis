#include <chrono>
#include <vector>

#include "data_sorting.h"

std::vector<long long> radix_sort(std::vector<int> data){
	//index 0 = swaps; index 1 = comparisons; index 2 = time;
    std::vector<long long> results;
    results.resize(3);
    int cycles = 0;
    int size_data = data.size();
    while(size_data != 0){
        cycles++;
        size_data /= 10;
    }
    std::vector<std::vector<long long>> digit_counter;
    digit_counter.resize(10);
    auto begin = std::chrono::system_clock::now();
    int divisor = 1;
    for(int i = 0; i < cycles; i++){
        for(int j = 0; j < data.size(); j++){
            int current_digit = data[j] / divisor % 10;
            switch (current_digit)
            {
            case 0:
                digit_counter[0].push_back(data[j]);
                break;
            case 1:
                digit_counter[1].push_back(data[j]);
                break;
            case 2:
                digit_counter[2].push_back(data[j]);
                break;
            case 3:
                digit_counter[3].push_back(data[j]);
                break;
            case 4:
                digit_counter[4].push_back(data[j]);
                break;
            case 5:
                digit_counter[5].push_back(data[j]);
                break;
            case 6:
                digit_counter[6].push_back(data[j]);
                break;
            case 7:
                digit_counter[7].push_back(data[j]);
                break;
            case 8:
                digit_counter[8].push_back(data[j]);
                break;
            case 9:
                digit_counter[9].push_back(data[j]);
                break;
            default:
                break;
            }
            results[0]++; 
        }
        int index = 0;
        for(int i =  0; i < digit_counter.size(); i++){
            while(digit_counter[i].size() != 0){
                int num = digit_counter[i].front();
                data[index] = digit_counter[i].front();
                digit_counter[i].erase(digit_counter[i].begin());
                index++;
            }
        }
        divisor *= 10;
    }
    auto finish = std::chrono::system_clock::now();
	std::chrono::duration<double> delta_time = finish - begin;
    //Time in milliseconds
    results[2] = delta_time.count() * 1000; 
    return results;
}
