#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "data_sorting.h"

using namespace std;

int main() {
	/*int i = 1000;
	while (i < 10000001) {
		ofstream out_file("dataset_" + to_string(i) + ".dat");
		random_number_generator(out_file, i);
		out_file.close();
		i *= 10;
	}*/
	//random_number_file_generator("dataset3_", 10, 20, 5);

	
        std::ifstream file("dataset2_10000.dat");
	std::vector<int> data;
    int value;
    while(file >> value){
        data.push_back(value);
    }
	file.close();

	//std::chrono::milliseconds timespan(1000);
	//std::this_thread::sleep_for(timespan); 
	std::vector<long long> bubble_sort_results = bubble_sort(data);
	std::vector<long long> insertion_sort_results = insertion_sort(data);
	std::vector<long long> selection_sort_results = selection_sort(data);
	std::vector<long long> shell_sort_results = shell_sort(data);
	//std::vector<long long> merge_sort_results = merge_sort(data);
	//std::vector<long long> radix_sort_results = radix_sort(data);
	//std::vector<long long> quick_sort_results = quick_sort(data);
	for(int i = 0; i < shell_sort_results.size(); i++){
		cout << shell_sort_results[i] << endl;
	}
}
