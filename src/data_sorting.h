#ifndef DS
#define DS

#include <fstream>
#include <vector>

void command_line();
void random_number_generator(std::ofstream&, int);
void random_number_file_generator(std::string, unsigned long long, unsigned long long, int);
std::vector<long long> bubble_sort(std::vector<int>);
std::vector<long long> insertion_sort(std::vector<int>);
std::vector<long long> selection_sort(std::vector<int>);
std::vector<long long> shell_sort(std::vector<int>);
std::vector<long long> quick_sort(std::vector<int>);
std::vector<long long> merge_sort(std::vector<int>);
std::vector<long long> heap_sort(std::vector<int>);
std::vector<long long> radix_sort(std::vector<int>);

#endif
