#include <fstream>
#include <fstream>
#include <string>

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
	random_number_file_generator("dataset2_", 1000, 10000000, 10);
}