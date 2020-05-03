#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "data_sorting.h"

using namespace std;

static bool command_exists(string commands[], int size, string command){
	for(int i = 0; i < size; i++){
		if(command == commands[i]){
			return true;
		}
	}
	return false;
}

static vector<string> split_string(string input){
	vector<string> out;
	int end_space = input.find(' ');
	int end_semicolon = input.find(';');
	if(end_semicolon == -1){
		return out;
	}
	while(true){
		if(end_space == -1 && end_semicolon != -1){
			out.push_back(input.substr(0, end_semicolon));
			break;
		}
		out.push_back(input.substr(0, input.find(' ')));
		input = input.substr(input.find(' ') + 1, input.length());
		end_space = input.find(' ');
		end_semicolon = input.find(';');
		if(end_space == -1 && end_semicolon == -1){
			break;
		}
	}
}

static void command_line(){
	string commands[] = {"generate", "all", "show", "help", "set_path", "exit"};
	string input = "";
	vector<string> parsed_string;
	while(true){
		cout << ">> ";
		getline(std::cin, input);
		parsed_string = split_string(input);
		if(parsed_string.size() == 0){
			cout << "Missing ';' at end of line. Try again." << endl;
			continue;
		}
		if(!command_exists(commands,sizeof(commands)/sizeof(commands[0]),parsed_string[0])){
			cout << "Invalid input. Type 'help' to open manual." << endl;
			continue;
		}
	}
	
}

int main() {
	/*
	/*int i = 1000;
	while (i < 10000001) {
		ofstream out_file("dataset_" + to_string(i) + ".dat");
		random_number_generator(out_file, i);
		out_file.close();
		i *= 10;
	}
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
	*/
	command_line();
}
