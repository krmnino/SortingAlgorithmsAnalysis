#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <filesystem>

#include "data_sorting.h"

using namespace std;
namespace fs = filesystem;

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
	return out;
}

static void command_line(){
	string commands[] = {"generate", "single_run", "show_res", "save_res", "delete_res", "set_path", "show_path", "help", "plot", "exit"};
	vector<vector<long long>> bubble_results;
	vector<vector<long long>> insertion_results;
	vector<vector<long long>> selection_results;
	vector<vector<long long>> shell_results;
	vector<vector<long long>> merge_results;
	vector<vector<long long>> quick_results;
	vector<vector<long long>> radix_results;
	//string directory_path = "";
	string directory_path = "/home/kurt/temporary"; //////////////////////////////////////////////////
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
		if(parsed_string[0] == "help"){
			cout << "generate" << endl;
			cout << "run" << endl;
			cout << "results" << endl;
			cout << "exit" << endl;
		}
		if(parsed_string[0] == "generate"){
			if(parsed_string.size() != 4){
				cout << "Usage: generate [lower bound] [upper_bound] [factor];" << endl;
				continue;
			}
			else if(directory_path == ""){
				cout << "Directory path not set yet. Type 'set_path [FULL_DIRECTORY_PATH];' to set it up." << endl;
				continue;
			}
			bool valid_parameter = true;
			while(true){
				try{
					for(int i = 1; i < parsed_string.size(); i++){
						int temp = stoi(parsed_string[i]);
					}
					break;
				}
				catch(exception e){
					cout << "Invalid input. Parameters must be integers." << endl;
					valid_parameter = false;
					break;
				}
			}
			if(!valid_parameter) continue;
			if(stoi(parsed_string[1]) >= stoi(parsed_string[2])){
				cout << "[upper_bound] must be greater than [lower_bound]." << endl;
				continue;
			}
			random_number_file_generator(directory_path, stoi(parsed_string[1]), stoi(parsed_string[2]), stoi(parsed_string[3]));
		}
		if(parsed_string[0] == "single_run"){
			if(directory_path == ""){
				cout << "Directory path not set yet. Type 'set_path [FULL_DIRECTORY_PATH];' to set it up." << endl;
				continue;
			}
			vector<tuple<int, string>> file_names;
			for (auto& entry : fs::directory_iterator(directory_path)) {
				string path = entry.path().string();
				string size_str = path.substr(path.find_last_of('/') + 1);
				size_str = size_str.erase(size_str.find('.'));
				int size = stoi(size_str);
				file_names.push_back(make_tuple(size, path));
			}
			//sort filenames by size here...
			for(int i = 0; i < file_names.size(); i++){
				ifstream file(std::get<1>(file_names[i]));
				vector<int> data;
				int value;
				while(file >> value){
					data.push_back(value);
				}
				for(int j = 0; j < 7; j++){
					switch(j){
						case 0:
						bubble_results.push_back(bubble_sort(data));
						cout << "PASS " << i << "Bubble sort completed." << endl;
						break;
						case 1:
						insertion_results.push_back(insertion_sort(data));
						cout << "PASS " << i << "Insertion sort completed." << endl;
						break;
						case 2:
						selection_results.push_back(selection_sort(data));
						cout << "PASS " << i << "Selection sort completed." << endl;
						break;
						case 3:
						shell_results.push_back(shell_sort(data));
						cout << "PASS " << i << "Shell sort completed." << endl;
						break;
						case 4:
						merge_results.push_back(merge_sort(data));
						cout << "PASS " << i << "Merge sort completed." << endl;
						break;
						case 5:
						quick_results.push_back(quick_sort(data));
						cout << "PASS " << i << "Quick sort completed." << endl;
						break;
						case 6:
						radix_results.push_back(radix_sort(data));
						cout << "PASS " << i << "Radix sort completed." << endl;
						break;
						default:
						break;
					}
				}
			}
		}
		if(parsed_string[0] == "show_res"){
			if(parsed_string.size() != 2){
				cout << "Usage: show_res [SORT_RESULTS_FLAG]" << endl;
				cout << "SORT_RESULTS_FLAG indicates which sorting algorithm must be printed" << endl;
				cout << "0: Bubble sort" << endl;
				cout << "1: Insertion sort" << endl;
				cout << "2: Selection sort" << endl;
				cout << "3: Shell sort" << endl;
				cout << "4: Merge sort" << endl;
				cout << "5: Quick sort" << endl;
				cout << "6: Radix sort" << endl;
				continue;
			}
			try{
				int temp = stoi(parsed_string[1]);
			}				
			catch(exception e){
				cout << "Invalid input. Sort flag must be integers." << endl;
				continue;
			}
			string out = "Size | Swaps | Comparisons | Time(ms)\n";
			if(bubble_results.size() == 0 || insertion_results.size() == 0 ||
			   selection_results.size() == 0 || shell_results.size() == 0 ||
			   merge_results.size() == 0 || quick_results.size() == 0 || radix_results.size() == 0){
				cout << "Result tables are empty. Type 'single_run' to measure sorting algorithms performance." << endl;
				continue;
			}
			switch(stoi(parsed_string[1])){
				case 0:
				for(int i = 0; i < bubble_results.size(); i++){
					for(int j = 0; j < bubble_results[i].size(); j++){
						out += bubble_results[i][j] + "\t";
					}
					if(i != bubble_results.size()-1) out += "\n";
				}
				break;
				case 1:
				for(int i = 0; i < insertion_results.size(); i++){
					for(int j = 0; j < insertion_results[i].size(); j++){
						out += insertion_results[i][j] + "\t";
					}
					if(i != insertion_results.size()-1) out += "\n";
				}
				break;
				case 2:
				for(int i = 0; i < selection_results.size(); i++){
					for(int j = 0; j < selection_results[i].size(); j++){
						out += selection_results[i][j] + "\t";
					}
					if(i != selection_results.size()-1) out += "\n";
				}
				break;
				case 3:
				for(int i = 0; i < shell_results.size(); i++){
					for(int j = 0; j < shell_results[i].size(); j++){
						out += shell_results[i][j] + "\t";
					}
					if(i != shell_results.size()-1) out += "\n";
				}
				break;
				case 4:
				for(int i = 0; i < merge_results.size(); i++){
					for(int j = 0; j < merge_results[i].size(); j++){
						out += merge_results[i][j] + "\t";
					}
					if(i != merge_results.size()-1) out += "\n";
				}
				break;
				case 5:
				for(int i = 0; i < quick_results.size(); i++){
					for(int j = 0; j < quick_results[i].size(); j++){
						out += quick_results[i][j] + "\t";
					}
					if(i != quick_results.size()-1) out += "\n";
				}
				break;
				case 6:
				for(int i = 0; i < radix_results.size(); i++){
					for(int j = 0; j < radix_results[i].size(); j++){
						out += radix_results[i][j] + "\t";
					}
					if(i != radix_results.size()-1) out += "\n";
				}
				break;
				default:
				break;
			}
			cout << out << endl;
			continue;
		}
		if(parsed_string[0] == "save_res"){
			if(parsed_string.size() != 3){
				cout << "Usage: save_res [SORT_RESULTS_FLAG] [FULL_DIRECTORY_PATH]" << endl;
				cout << "SORT_RESULTS_FLAG indicates which sorting algorithm must be printed" << endl;
				cout << "0: Bubble sort" << endl;
				cout << "1: Insertion sort" << endl;
				cout << "2: Selection sort" << endl;
				cout << "3: Shell sort" << endl;
				cout << "4: Merge sort" << endl;
				cout << "5: Quick sort" << endl;
				cout << "6: Radix sort" << endl;
				continue;
			}
			try{
				int temp = stoi(parsed_string[1]);
			}				
			catch(exception e){
				cout << "Invalid input. Sort flag must be integers." << endl;
				continue;
			}
			if(!fs::is_directory(parsed_string[1])){
				cout << parsed_string[1] <<" is not a valid directory path. Try again." << endl;
				continue;
			}
			string out = "Sort,Swaps,Comparisons,Time(ms)\n";
			if(bubble_results.size() == 0 || insertion_results.size() == 0 ||
			   selection_results.size() == 0 || shell_results.size() == 0 ||
			   merge_results.size() == 0 || quick_results.size() == 0 || radix_results.size() == 0){
				cout << "Result tables are empty. Type 'single_run' to measure sorting algorithms performance." << endl;
				continue;
			}
			switch(stoi(parsed_string[1])){
				case 0:
				for(int i = 0; i < bubble_results.size(); i++){
					for(int j = 0; j < bubble_results[i].size(); j++){
						out += bubble_results[i][j] + "\t";
					}
					if(i != bubble_results.size()-1) out += "\n";
				}
				break;
				case 1:
				for(int i = 0; i < insertion_results.size(); i++){
					for(int j = 0; j < insertion_results[i].size(); j++){
						out += insertion_results[i][j] + "\t";
					}
					if(i != insertion_results.size()-1) out += "\n";
				}
				break;
				case 2:
				for(int i = 0; i < selection_results.size(); i++){
					for(int j = 0; j < selection_results[i].size(); j++){
						out += selection_results[i][j] + "\t";
					}
					if(i != selection_results.size()-1) out += "\n";
				}
				break;
				case 3:
				for(int i = 0; i < shell_results.size(); i++){
					for(int j = 0; j < shell_results[i].size(); j++){
						out += shell_results[i][j] + "\t";
					}
					if(i != shell_results.size()-1) out += "\n";
				}
				break;
				case 4:
				for(int i = 0; i < merge_results.size(); i++){
					for(int j = 0; j < merge_results[i].size(); j++){
						out += merge_results[i][j] + "\t";
					}
					if(i != merge_results.size()-1) out += "\n";
				}
				break;
				case 5:
				for(int i = 0; i < quick_results.size(); i++){
					for(int j = 0; j < quick_results[i].size(); j++){
						out += quick_results[i][j] + "\t";
					}
					if(i != quick_results.size()-1) out += "\n";
				}
				break;
				case 6:
				for(int i = 0; i < radix_results.size(); i++){
					for(int j = 0; j < radix_results[i].size(); j++){
						out += radix_results[i][j] + "\t";
					}
					if(i != radix_results.size()-1) out += "\n";
				}
				break;
				default:
				break;
			}
			ofstream file(parsed_string[1] + "results.csv");
			file << out;
			file.close();
			
			cout << "Results saved in: " << parsed_string[1] << "results.csv" << endl;
			continue;
		}
		if(parsed_string[0] == "delete_res"){
			if(bubble_results.size() == 0 || insertion_results.size() == 0 ||
			   selection_results.size() == 0 || shell_results.size() == 0 ||
			   merge_results.size() == 0 || quick_results.size() == 0 || radix_results.size() == 0){
				cout << "Result tables are empty. Type 'single_run' to measure sorting algorithms performance." << endl;
				continue;
			}
			for(int i = 0; i < bubble_results.size(); i++){
				for(int j = 0; j < bubble_results[i].size(); j++){
					bubble_results[i][j] = 0;
				}
			}
			for(int i = 0; i < insertion_results.size(); i++){
				for(int j = 0; j < insertion_results[i].size(); j++){
					insertion_results[i][j] = 0;
				}
			}
			for(int i = 0; i < selection_results.size(); i++){
				for(int j = 0; j < selection_results[i].size(); j++){
					selection_results[i][j] = 0;
				}
			}
			for(int i = 0; i < shell_results.size(); i++){
				for(int j = 0; j < shell_results[i].size(); j++){
					shell_results[i][j] = 0;
				}
			}
			for(int i = 0; i < merge_results.size(); i++){
				for(int j = 0; j < merge_results[i].size(); j++){
					merge_results[i][j] = 0;
				}
			}
			for(int i = 0; i < quick_results.size(); i++){
				for(int j = 0; j < quick_results[i].size(); j++){
					quick_results[i][j] = 0;
				}
			}
			for(int i = 0; i < radix_results.size(); i++){
				for(int j = 0; j < radix_results[i].size(); j++){
					radix_results[i][j] = 0;
				}
			}
			cout << "All results deleted." << endl;
			continue;
		}
		if(parsed_string[0] == "set_path"){
			if(parsed_string.size() != 2){
				cout << "Usage: set_path [FULL_DIRECTORY_PATH]" << endl;
				continue;
			}
			if(!fs::is_directory(parsed_string[1])){
				cout << parsed_string[1] <<" is not a valid directory path. Try again." << endl;
				continue;
			}
			directory_path = parsed_string[1];
			cout << "Directory path set to: " << directory_path << endl;
			continue;
		}
		if(parsed_string[0] == "show_path"){
			cout << "Path: " << directory_path << endl;
			continue;
		}
		if(parsed_string[0] == "clear"){
			system("clear");
		}
		if(parsed_string[0] == "exit"){
			break;
		}
	}
	
}

int main() {
	command_line();
}
