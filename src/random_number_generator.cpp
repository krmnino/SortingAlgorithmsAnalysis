#include <string>
#include <chrono>
#include <iostream>

#include "data_sorting.h"

using namespace std;

void random_number_file_generator(string path, unsigned long long lower_bound, unsigned long long upper_bound, int increment) {
	while (lower_bound < upper_bound + 1) {
		ofstream out_file(path + "/" + to_string(lower_bound) + ".dat");
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
	long long i = 0;
	long long j = 0;
	while (i < upper_bound) {
		j = rand() * millis % upper_bound;
		if(j < 0) 
			out_file << to_string(j * -1) << endl;
		else
			out_file << to_string(j) << endl;
		i++;
	}
}
