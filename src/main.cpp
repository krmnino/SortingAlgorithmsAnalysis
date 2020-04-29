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
	//random_number_file_generator("dataset2_", 1000, 10000000, 10);
	std::ifstream file("dataset2_1000000.dat");
	std::vector<int> data;
    int value;
    while(file >> value){
        data.push_back(value);
    }
	file.close();
	
	//std::chrono::milliseconds timespan(1000);
	//std::this_thread::sleep_for(timespan);
	std::vector<long long> shell_sort_results = shell_sort(data);
	for(int i = 0; i < shell_sort_results.size(); i++){
		cout << shell_sort_results[i] << endl;
	}
}