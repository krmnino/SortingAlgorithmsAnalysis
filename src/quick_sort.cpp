#include <iostream>
#include <chrono>
#include <vector>

#include "data_sorting.h"

static int partition(std::vector<int>& a, int lo, int hi, std::vector<long long>& results){
	int pivot = a[hi];	
	int i = (lo - 1);   
    for (int j = lo; j <= hi - 1; j++)  
    {  
		results[1]++;
        if (a[j] < pivot)  
        {  
            i++; 
			int t = a[i];  
    		a[i] = a[j];  
    		a[j] = t;
			results[0]++; 
        }  
    }  
	int t = a[i + 1];  
    a[i + 1] = a[hi];  
    a[hi] = t;
	results[0]++;
    return (i + 1);    
}

static void qsort(std::vector<int>& a, int lo, int hi, std::vector<long long>& results){
	results[1]++;  
	if (lo < hi)  
    {  
        int pi = partition(a, lo, hi, results);    
        qsort(a, lo, pi - 1, results);  
        qsort(a, pi + 1, hi, results);  
    }  
}
  
std::vector<long long> quick_sort(std::vector<int> a){
    int n = a.size();
    std::vector<long long> results;
    results.resize(3);
    auto begin = std::chrono::system_clock::now();
    qsort(a, 0, n - 1, results);
    auto finish = std::chrono::system_clock::now();
    std::chrono::duration<double> delta_time = finish - begin;
    //Time in milliseconds
    results[2] = delta_time.count() * 1000;
    return results;
}
