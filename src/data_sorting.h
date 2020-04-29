#ifndef DS
#define DS

#include <fstream>
#include <vector>

void random_number_generator(std::ofstream&, int);
void random_number_file_generator(std::string, unsigned long long, unsigned long long, int);
std::vector<double> bubble_sort(std::vector<int>);
std::vector<double> insertion_sort(std::vector<int>);
std::vector<double> selection_sort(std::vector<int>);
std::vector<long long> shell_sort(std::vector<int>);
std::vector<double> quick_sort(std::vector<int>);
std::vector<double> merge_sort(std::vector<int>);
std::vector<double> heap_sort(std::vector<int>);
std::vector<double> radix_sort(std::vector<int>);

#endif