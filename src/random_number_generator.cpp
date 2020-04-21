#include <string>
#include <chrono>
#include <iostream>

#include "data_sorting.h"

using namespace std;

void random_number_file_generator(string name_header, unsigned long long lower_bound, unsigned long long upper_bound, int increment) {
	while (lower_bound < upper_bound + 1) {
		ofstream out_file(name_header + to_string(lower_bound) + ".dat");
		random_number_generator(out_file, lower_bound);
		out_file.close();
		lower_bound *= increment;
	}
}

void random_number_generator(ofstream& out_file, int upper_bound) {
	chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	auto millis = chrono::duration_cast<chrono::milliseconds>(duration).count();
	srand(millis);
	unsigned long long i = 0;
	while (i < upper_bound) {
		out_file << to_string(rand() * millis % upper_bound) << endl;
		i++;
	}
}