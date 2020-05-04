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

	for(int i = 1; i < data.size(); i++)
		{
			for(int j = i; j > 0; j--)
			{
				results[1]++;
				if(data[j] < data[j-1])
				{
					int temp = data[j];
					data[j] = data[j-1];
					data[j-1] = temp;
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

