#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <bits/stdc++.h>

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

static bool sort_vec_tuple(const tuple<int, string>& a, const tuple<int, string>& b){
	return (get<0>(a) < get<0>(b));
}

static void command_line(){
	string commands[] = {"generate", "run", "show_res", "save_res", "save_all_res", "delete_res",
						 "set_path", "show_path", "help", "plot_res", "plot_all_res", "clear", "exit"};
	vector<vector<long long>> bubble_results;
	vector<vector<long long>> insertion_results;
	vector<vector<long long>> selection_results;
	vector<vector<long long>> shell_results;
	vector<vector<long long>> merge_results;
	vector<vector<long long>> quick_results;
	vector<vector<long long>> radix_results;
	//string directory_path = "";
	string directory_path = "/home/kurt/temporary/sets/";
	string input = "";
	vector<string> parsed_string;
	cout << "=== Sorting Algorithm Performance Test Program ===\nAuthors: Ethan Breban, Korhan Citlak, Kurt Manrique-Nino." << endl;
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
			cout << "generate 			Generates dataset within a given range with random values" << endl;
			cout << "					Usage: generate [lower_bound] [upper_bound] [increment_factor];" << endl;
			cout << "run				Test all algorithms using generated datasets" << endl;
			cout << "					Usage: run;" << endl;
			cout << "show_res			Display performance resuls of a specific algorithm." << endl;
			cout << "					Usage: show_res [SORT_RESULTS_FLAG];" << endl;
			cout << "save_res			Save performance resuls of a specific algorithm given a directory path." << endl;
			cout << "					Usage: save_res [SORT_RESULTS_FLAG] [FULL_DIRECTORY_PATH];" << endl;
			cout << "save_all_res			Save performance resuls of all algorithm given a directory path." << endl;
			cout << "					Usage: save_res [FULL_DIRECTORY_PATH];" << endl;
			cout << "delete_res			Deletes ALL performance results." << endl;
			cout << "					Usage: delete_res;" << endl;
			cout << "set_path			Set directory path where the program will read/write datasets" << endl;
			cout << "					Usage: set_path [FULL_DIRECTORY_PATH];" << endl;
			cout << "show_path			Show directory path where the program will read/write datasets" << endl;
			cout << "					Usage: show_path;" << endl;
			cout << "help				Display program menu with command definitions." << endl; 
			cout << "					Usage: help;" << endl;
			cout << "exit				Exit the program." << endl;
			cout << "					Usage: exit;" << endl;

		}
		if(parsed_string[0] == "generate"){
			if(parsed_string.size() != 4){
				cout << "Usage: generate [lower bound] [upper_bound] [increment_factor];" << endl;
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
		if(parsed_string[0] == "run"){
			if(directory_path == ""){
				cout << "Directory path not set yet. Type 'set_path [FULL_DIRECTORY_PATH];' to set it up." << endl;
				continue;
			}
			bubble_results.clear();
			insertion_results.clear();
			selection_results.clear();
			shell_results.clear();
			merge_results.clear();
			quick_results.clear();
			radix_results.clear();
			vector<tuple<int, string>> file_names;
			bool valid_filenames = true;
			for (auto& entry : fs::directory_iterator(directory_path)) {
				string path;
				string size_str;
				try{
					path = entry.path().string();
					size_str = path.substr(path.find_last_of('/') + 1);
					size_str = size_str.erase(size_str.find('.'));
					stoi(size_str);
				}
				catch(exception e){
					valid_filenames = false;
					break;
				}
				path = entry.path().string();
				size_str = path.substr(path.find_last_of('/') + 1);
				size_str = size_str.erase(size_str.find('.'));
				stoi(size_str);
				file_names.push_back(make_tuple(stoi(size_str), path));
			}
			if(!valid_filenames){
				cout << directory_path << "must contain datasets ONLY. Remove any non-compatible files or directories from it." << endl;
				continue;
			}
			sort(file_names.begin(), file_names.end(), sort_vec_tuple);
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
						bubble_results[i].insert(bubble_results[i].begin(), data.size());
						cout << "DATASET SIZE " << data.size() << ": Bubble sort completed." << endl;
						break;
						case 1:
						insertion_results.push_back(insertion_sort(data));
						insertion_results[i].insert(insertion_results[i].begin(), data.size());
						cout << "DATASET SIZE " << data.size() << ": Insertion sort completed." << endl;
						break;
						case 2:
						selection_results.push_back(selection_sort(data));
						selection_results[i].insert(selection_results[i].begin(), data.size());
						cout << "DATASET SIZE " << data.size() << ": Selection sort completed." << endl;
						break;
						case 3:
						shell_results.push_back(shell_sort(data));
						shell_results[i].insert(shell_results[i].begin(), data.size());
						cout << "DATASET SIZE " << data.size() << ": Shell sort completed." << endl;
						break;
						case 4:
						merge_results.push_back(merge_sort(data));
						merge_results[i].insert(merge_results[i].begin(), data.size());
						cout << "DATASET SIZE " << data.size() << ": Merge sort completed." << endl;
						break;
						case 5:
						quick_results.push_back(quick_sort(data));
						quick_results[i].insert(quick_results[i].begin(), data.size());
						cout << "DATASET SIZE " << data.size() << ": Quick sort completed." << endl;
						break;
						case 6:
						radix_results.push_back(radix_sort(data));
						radix_results[i].insert(radix_results[i].begin(), data.size());
						cout << "DATASET SIZE " << data.size() << ": Radix sort completed." << endl;
						break;
						default:
						break;
					}
				}
			}
			continue;
		}
		if(parsed_string[0] == "show_res"){
			if(parsed_string.size() != 2){
				cout << "Usage: show_res [SORT_RESULTS_FLAG];" << endl;
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
			if(stoi(parsed_string[1]) > 6){
				cout << "SORT_RESULTS_FLAG range must be between 0 and 6." << endl;
				cout << "0: Bubble sort" << endl;
				cout << "1: Insertion sort" << endl;
				cout << "2: Selection sort" << endl;
				cout << "3: Shell sort" << endl;
				cout << "4: Merge sort" << endl;
				cout << "5: Quick sort" << endl;
				cout << "6: Radix sort" << endl;
				continue;
			}
			if(bubble_results.size() == 0 || insertion_results.size() == 0 ||
			   selection_results.size() == 0 || shell_results.size() == 0 ||
			   merge_results.size() == 0 || quick_results.size() == 0 || radix_results.size() == 0){
				cout << "Result tables are empty. Type 'run' to measure sorting algorithms performance." << endl;
				continue;
			}
			string out_results = "Size | Swaps | Comparisons | Time(ms)\n";
			switch(stoi(parsed_string[1])){
				case 0:
				cout << "Bubble Sort" << endl;
				for(int i = 0; i < bubble_results.size(); i++){
					for(int j = 0; j < bubble_results[i].size(); j++){
						out_results += to_string(bubble_results[i][j]) + "\t";
					}
					if(i != bubble_results.size()-1) out_results += "\n";
				}
				break;
				case 1:
				cout << "Insertion Sort" << endl;
				for(int i = 0; i < insertion_results.size(); i++){
					for(int j = 0; j < insertion_results[i].size(); j++){
						out_results += to_string(insertion_results[i][j]) + "\t";
					}
					if(i != insertion_results.size()-1) out_results += "\n";
				}
				break;
				case 2:
				cout << "Selection Sort" << endl;
				for(int i = 0; i < selection_results.size(); i++){
					for(int j = 0; j < selection_results[i].size(); j++){
						out_results += to_string(selection_results[i][j]) + "\t";
					}
					if(i != selection_results.size()-1) out_results += "\n";
				}
				break;
				case 3:
				cout << "Shell Sort" << endl;
				for(int i = 0; i < shell_results.size(); i++){
					for(int j = 0; j < shell_results[i].size(); j++){
						out_results += to_string(shell_results[i][j]) + "\t";
					}
					if(i != shell_results.size()-1) out_results += "\n";
				}
				break;
				case 4:
				cout << "Merge Sort" << endl;
				for(int i = 0; i < merge_results.size(); i++){
					for(int j = 0; j < merge_results[i].size(); j++){
						out_results += to_string(merge_results[i][j]) + "\t";
					}
					if(i != merge_results.size()-1) out_results += "\n";
				}
				break;
				case 5:
				cout << "Quick Sort" << endl;
				for(int i = 0; i < quick_results.size(); i++){
					for(int j = 0; j < quick_results[i].size(); j++){
						out_results += to_string(quick_results[i][j]) + "\t";
					}
					if(i != quick_results.size()-1) out_results += "\n";
				}
				break;
				case 6:
				cout << "Radix Sort" << endl;
				for(int i = 0; i < radix_results.size(); i++){
					for(int j = 0; j < radix_results[i].size(); j++){
						out_results += to_string(radix_results[i][j]) + "\t";
					}
					if(i != radix_results.size()-1) out_results += "\n";
				}
				break;
				default:
				break;
			}
			cout << out_results << endl;
			continue;
		}
		if(parsed_string[0] == "save_res"){
			if(parsed_string.size() != 3){
				cout << "Usage: save_res [SORT_RESULTS_FLAG] [FULL_DIRECTORY_PATH];" << endl;
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
				stoi(parsed_string[1]);
			}				
			catch(exception e){
				cout << "Invalid input. Sort flag must be integers." << endl;
				continue;
			}
			if(stoi(parsed_string[1]) > 6){
				cout << "SORT_RESULTS_FLAG range must be between 0 and 6." << endl;
				cout << "0: Bubble sort" << endl;
				cout << "1: Insertion sort" << endl;
				cout << "2: Selection sort" << endl;
				cout << "3: Shell sort" << endl;
				cout << "4: Merge sort" << endl;
				cout << "5: Quick sort" << endl;
				cout << "6: Radix sort" << endl;
				continue;
			}
			if(!fs::is_directory(parsed_string[2])){
				cout << parsed_string[1] <<" is not a valid directory path. Try again." << endl;
				continue;
			}
			if(bubble_results.size() == 0 || insertion_results.size() == 0 ||
			   selection_results.size() == 0 || shell_results.size() == 0 ||
			   merge_results.size() == 0 || quick_results.size() == 0 || radix_results.size() == 0){
				cout << "Result tables are empty. Type 'run' to measure sorting algorithms performance." << endl;
				continue;
			}
			string sort_name = "";
			string out = "Size,Swaps,Comparisons,Time(ms)\n";
			switch(stoi(parsed_string[1])){
				case 0:
				sort_name = "/bubble_sort";
				for(int i = 0; i < bubble_results.size(); i++){
					for(int j = 0; j < bubble_results[i].size(); j++){
						out += to_string(bubble_results[i][j]) + ",";
					}
					if(i != bubble_results.size()-1) out += "\n";
				}
				break;
				case 1:
				sort_name = "/insertion_sort";
				for(int i = 0; i < insertion_results.size(); i++){
					for(int j = 0; j < insertion_results[i].size(); j++){
						out += to_string(insertion_results[i][j]) + ",";
					}
					if(i != insertion_results.size()-1) out += "\n";
				}
				break;
				case 2:
				sort_name = "/selection_sort";
				for(int i = 0; i < selection_results.size(); i++){
					for(int j = 0; j < selection_results[i].size(); j++){
						out += to_string(selection_results[i][j]) + ",";
					}
					if(i != selection_results.size()-1) out += "\n";
				}
				break;
				case 3:
				sort_name = "/shell_sort";
				for(int i = 0; i < shell_results.size(); i++){
					for(int j = 0; j < shell_results[i].size(); j++){
						out += to_string(shell_results[i][j]) + ",";
					}
					if(i != shell_results.size()-1) out += "\n";
				}
				break;
				case 4:
				sort_name = "/merge_sort";
				for(int i = 0; i < merge_results.size(); i++){
					for(int j = 0; j < merge_results[i].size(); j++){
						out += to_string(merge_results[i][j]) + ",";
					}
					if(i != merge_results.size()-1) out += "\n";
				}
				break;
				case 5:
				sort_name = "/quick_sort";
				for(int i = 0; i < quick_results.size(); i++){
					for(int j = 0; j < quick_results[i].size(); j++){
						out += to_string(quick_results[i][j]) + ",";
					}
					if(i != quick_results.size()-1) out += "\n";
				}
				break;
				case 6:
				sort_name = "/radix_sort";
				for(int i = 0; i < radix_results.size(); i++){
					for(int j = 0; j < radix_results[i].size(); j++){
						out += to_string(radix_results[i][j]) + ",";
					}
					if(i != radix_results.size()-1) out += "\n";
				}
				break;
				default:
				break;
			}
			ofstream file(parsed_string[2] + sort_name + "_results.csv");
			file << out;
			file.close();
			cout << "Results saved in: " << parsed_string[2] + sort_name << "_results.csv" << endl;
			continue;
		}
		if(parsed_string[0] == "save_all_res"){
			if(parsed_string.size() != 2){
				cout << "Usage: save_res [FULL_DIRECTORY_PATH]" << endl;
				continue;
			}
			if(!fs::is_directory(parsed_string[1])){
				cout << parsed_string[1] <<" is not a valid directory path. Try again." << endl;
				continue;
			}
			if(bubble_results.size() == 0 || insertion_results.size() == 0 ||
			   selection_results.size() == 0 || shell_results.size() == 0 ||
			   merge_results.size() == 0 || quick_results.size() == 0 || radix_results.size() == 0){
				cout << "Result tables are empty. Type 'run' to measure sorting algorithms performance." << endl;
				continue;
			}
			string out = "";
			{
				out = "Size,Swaps,Comparisons,Time(ms)\n";
				for(int i = 0; i < bubble_results.size(); i++){
					for(int j = 0; j < bubble_results[i].size(); j++){
						out += to_string(bubble_results[i][j]);
						if(j != bubble_results[j].size()-1) out += ",";
					}
					if(i != bubble_results.size()-1) out += "\n";
				}
				ofstream file(parsed_string[1] + "/bubble_sort_results.csv");
				file << out;
				file.close();
				cout << "Results saved in: " << parsed_string[1] + "/bubble_sort_results.csv" << endl;

			}
			{
				out = "Size,Swaps,Comparisons,Time(ms)\n";
				for(int i = 0; i < insertion_results.size(); i++){
					for(int j = 0; j < insertion_results[i].size(); j++){
						out += to_string(insertion_results[i][j]);
						if(j != insertion_results[j].size()-1) out += ",";
					}
					if(i != insertion_results.size()-1) out += "\n";
				}
				ofstream file(parsed_string[1] + "/insertion_sort_results.csv");
				file << out;
				file.close();
				cout << "Results saved in: " << parsed_string[1] + "/insertion_sort_results.csv" << endl;
			}
			{
				out = "Size,Swaps,Comparisons,Time(ms)\n";
				for(int i = 0; i < selection_results.size(); i++){
					for(int j = 0; j < selection_results[i].size(); j++){
						out += to_string(selection_results[i][j]);
						if(j != selection_results[j].size()-1) out += ",";
					}
					if(i != selection_results.size()-1) out += "\n";
				}
				ofstream file(parsed_string[1] + "/selection_sort_results.csv");
				file << out;
				file.close();
				cout << "Results saved in: " << parsed_string[1] + "/selection_sort_results.csv" << endl;
			}
			{
				out = "Size,Swaps,Comparisons,Time(ms)\n";
				for(int i = 0; i < shell_results.size(); i++){
					for(int j = 0; j < shell_results[i].size(); j++){
						out += to_string(shell_results[i][j]);
						if(j != shell_results[j].size()-1) out += ",";
					}
					if(i != shell_results.size()-1) out += "\n";
				}
				ofstream file(parsed_string[1] + "/shell_sort_results.csv");
				file << out;
				file.close();
				cout << "Results saved in: " << parsed_string[1] + "/shell_sort_results.csv" << endl;
			}
			{
				out = "Size,Swaps,Comparisons,Time(ms)\n";
				for(int i = 0; i < merge_results.size(); i++){
					for(int j = 0; j < merge_results[i].size(); j++){
						out += to_string(merge_results[i][j]);
						if(j != merge_results[j].size()-1) out += ",";
					}
					if(i != merge_results.size()-1) out += "\n";
				}
				ofstream file(parsed_string[1] + "/merge_sort_results.csv");
				file << out;
				file.close();
				cout << "Results saved in: " << parsed_string[1] + "/merge_sort_results.csv" << endl;
			}
			{
				out = "Size,Swaps,Comparisons,Time(ms)\n";
				for(int i = 0; i < quick_results.size(); i++){
					for(int j = 0; j < quick_results[i].size(); j++){
						out += to_string(quick_results[i][j]);
						if(j != quick_results[j].size()-1) out += ",";
					}
					if(i != quick_results.size()-1) out += "\n";
				}
				ofstream file(parsed_string[1] + "/quick_sort_results.csv");
				file << out;
				file.close();
				cout << "Results saved in: " << parsed_string[1] + "/quick_sort_results.csv" << endl;
			}
			{
				out = "Size,Swaps,Comparisons,Time(ms)\n";
				for(int i = 0; i < radix_results.size(); i++){
					for(int j = 0; j < radix_results[i].size(); j++){
						out += to_string(radix_results[i][j]);
						if(j != radix_results[j].size()-1) out += ",";
					}
					if(i != radix_results.size()-1) out += "\n";
				}
				ofstream file(parsed_string[1] + "/radix_sort_results.csv");
				file << out;
				file.close();
				cout << "Results saved in: " << parsed_string[1] + "/radix_sort_results.csv" << endl;
			}
			continue;
		}
		if(parsed_string[0] == "delete_res"){
			bubble_results.clear();
			insertion_results.clear();
			selection_results.clear();
			shell_results.clear();
			merge_results.clear();
			quick_results.clear();
			radix_results.clear();
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
		if(parsed_string[0] == "plot_res"){
			if(parsed_string.size() != 3){
				cout << "Usage: plot_res [SORT_RESULTS_FLAG] [FULL_DIRECTORY_PATH];" << endl;
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
				stoi(parsed_string[1]);
			}				
			catch(exception e){
				cout << "Invalid input. Sort flag must be integers." << endl;
				continue;
			}
			if(stoi(parsed_string[1]) > 6){
				cout << "SORT_RESULTS_FLAG range must be between 0 and 6." << endl;
				cout << "0: Bubble sort" << endl;
				cout << "1: Insertion sort" << endl;
				cout << "2: Selection sort" << endl;
				cout << "3: Shell sort" << endl;
				cout << "4: Merge sort" << endl;
				cout << "5: Quick sort" << endl;
				cout << "6: Radix sort" << endl;
				continue;
			}
			if(!fs::is_directory(parsed_string[2])){
				cout << parsed_string[1] <<" is not a valid directory path. Try again." << endl;
				continue;
			}
			if(bubble_results.size() == 0 || insertion_results.size() == 0 ||
			   selection_results.size() == 0 || shell_results.size() == 0 ||
			   merge_results.size() == 0 || quick_results.size() == 0 || radix_results.size() == 0){
				cout << "Result tables are empty. Type 'run' to measure sorting algorithms performance." << endl;
				continue;
			}
			string out = "";
			string sort_name;
			switch(stoi(parsed_string[1])){
				case 0:
				sort_name = "/bubble_sort";
				for(int i = 0; i < bubble_results.size(); i++){
					for(int j = 0; j < bubble_results[i].size(); j++){
						out += to_string(bubble_results[i][j]);
						if(j != bubble_results[j].size()-1) out += ",";
					}
					if(i != bubble_results.size()-1) out += "\n";
				}
				break;
				case 1:
				sort_name = "/insertion_sort";
				for(int i = 0; i < insertion_results.size(); i++){
					for(int j = 0; j < insertion_results[i].size(); j++){
						out += to_string(insertion_results[i][j]);
						if(j != insertion_results[j].size()-1) out += ",";
					}
					if(i != insertion_results.size()-1) out += "\n";
				}
				break;
				case 2:
				sort_name = "/selection_sort";
				for(int i = 0; i < selection_results.size(); i++){
					for(int j = 0; j < selection_results[i].size(); j++){
						out += to_string(selection_results[i][j]);
						if(j != selection_results[j].size()-1) out += ",";
					}
					if(i != selection_results.size()-1) out += "\n";
				}
				break;
				case 3:
				sort_name = "/shell_sort";
				for(int i = 0; i < shell_results.size(); i++){
					for(int j = 0; j < shell_results[i].size(); j++){
						out += to_string(shell_results[i][j]);
						if(j != shell_results[j].size()-1) out += ",";
					}
					if(i != shell_results.size()-1) out += "\n";
				}
				break;
				case 4:
				sort_name = "/merge_sort";
				for(int i = 0; i < merge_results.size(); i++){
					for(int j = 0; j < merge_results[i].size(); j++){
						out += to_string(merge_results[i][j]);
						if(j != merge_results[j].size()-1) out += ",";
					}
					if(i != merge_results.size()-1) out += "\n";
				}
				break;
				case 5:
				sort_name = "/quick_sort";
				for(int i = 0; i < quick_results.size(); i++){
					for(int j = 0; j < quick_results[i].size(); j++){
						out += to_string(quick_results[i][j]);
						if(j != quick_results[j].size()-1) out += ",";
					}
					if(i != quick_results.size()-1) out += "\n";
				}
				break;
				case 6:
				sort_name = "/radix_sort";
				for(int i = 0; i < radix_results.size(); i++){
					for(int j = 0; j < radix_results[i].size(); j++){
						out += to_string(radix_results[i][j]);
						if(j != radix_results[j].size()-1) out += ",";
					}
					if(i != radix_results.size()-1) out += "\n";
				}
				break;
				default:
				break;
			}
			ofstream file(parsed_string[2] + sort_name + ".csv");
			file << out;
			file.close();
			string launch_python = "python3 graph.py";
			launch_python += " " + parsed_string[1];
			launch_python += " " + parsed_string[2] + sort_name + ".csv";
			system(launch_python.c_str());
			continue;	
		}	
		if(parsed_string[0] == "plot_all_res"){
			if(parsed_string.size() != 2){
				cout << "Usage: plot_all [FULL_DIRECTORY_PATH]" << endl;
				continue;
			}
			if(!fs::is_directory(parsed_string[1])){
				cout << parsed_string[1] <<" is not a valid directory path. Try again." << endl;
				continue;
			}
			if(bubble_results.size() == 0 || insertion_results.size() == 0 ||
			   selection_results.size() == 0 || shell_results.size() == 0 ||
			   merge_results.size() == 0 || quick_results.size() == 0 || radix_results.size() == 0){
				cout << "Result tables are empty. Type 'run' to measure sorting algorithms performance." << endl;
				continue;
			}
			string out = "";
			string launch_python = "";
			{
				for(int i = 0; i < bubble_results.size(); i++){
					for(int j = 0; j < bubble_results[i].size(); j++){
						out += to_string(bubble_results[i][j]);
						if(j != bubble_results[j].size()-1) out += ",";
					}
					if(i != bubble_results.size()-1) out += "\n";
				}
				ofstream file(parsed_string[1] + "/bubble_sort.csv");
				file << out;
				file.close();
				launch_python = "python3 graph.py";
				launch_python += " 0";
				launch_python += " " + parsed_string[1] + "/bubble_sort.csv";
				system(launch_python.c_str());
			}
			{
				out = "";
				for(int i = 0; i < insertion_results.size(); i++){
					for(int j = 0; j < insertion_results[i].size(); j++){
						out += to_string(insertion_results[i][j]);
						if(j != insertion_results[j].size()-1) out += ",";
					}
					if(i != insertion_results.size()-1) out += "\n";
				}
				ofstream file(parsed_string[1] + "/insertion_sort.csv");
				file << out;
				file.close();
				launch_python = "python3 graph.py";
				launch_python += " 1";
				launch_python += " " + parsed_string[1] + "/insertion_sort.csv";
				system(launch_python.c_str());
			}
			{
				out = "";
				for(int i = 0; i < selection_results.size(); i++){
					for(int j = 0; j < selection_results[i].size(); j++){
						out += to_string(selection_results[i][j]);
						if(j != selection_results[j].size()-1) out += ",";
					}
					if(i != selection_results.size()-1) out += "\n";
				}
				ofstream file(parsed_string[1] + "/selection_sort.csv");
				file << out;
				file.close();
				launch_python = "python3 graph.py";
				launch_python += " 2";
				launch_python += " " + parsed_string[1] + "/selection_sort.csv";
				system(launch_python.c_str());
			}
			{
				out = "";
				for(int i = 0; i < shell_results.size(); i++){
					for(int j = 0; j < shell_results[i].size(); j++){
						out += to_string(shell_results[i][j]);
						if(j != shell_results[j].size()-1) out += ",";
					}
					if(i != shell_results.size()-1) out += "\n";
				}
				ofstream file(parsed_string[1] + "/shell_sort.csv");
				file << out;
				file.close();
				launch_python = "python3 graph.py";
				launch_python += " 3";
				launch_python += " " + parsed_string[1] + "/shell_sort.csv";
				system(launch_python.c_str());
			}
			{
				out = "";
				for(int i = 0; i < merge_results.size(); i++){
					for(int j = 0; j < merge_results[i].size(); j++){
						out += to_string(merge_results[i][j]);
						if(j != merge_results[j].size()-1) out += ",";
					}
					if(i != merge_results.size()-1) out += "\n";
				}
				ofstream file(parsed_string[1] + "/merge_sort.csv");
				file << out;
				file.close();
				launch_python = "python3 graph.py";
				launch_python += " 4";
				launch_python += " " + parsed_string[1] + "/merge_sort.csv";
				system(launch_python.c_str());
			}
			{
				out = "";
				for(int i = 0; i < quick_results.size(); i++){
					for(int j = 0; j < quick_results[i].size(); j++){
						out += to_string(quick_results[i][j]);
						if(j != quick_results[j].size()-1) out += ",";
					}
					if(i != quick_results.size()-1) out += "\n";
				}
				ofstream file(parsed_string[1] + "/quick_sort.csv");
				file << out;
				file.close();
				launch_python = "python3 graph.py";
				launch_python += " 5";
				launch_python += " " + parsed_string[1] + "/quick_sort.csv";
				system(launch_python.c_str());
			}
			{
				out = "";
				for(int i = 0; i < radix_results.size(); i++){
					for(int j = 0; j < radix_results[i].size(); j++){
						out += to_string(radix_results[i][j]);
						if(j != radix_results[j].size()-1) out += ",";
					}
					if(i != radix_results.size()-1) out += "\n";
				}
				ofstream file(parsed_string[1] + "/radix_sort.csv");
				file << out;
				file.close();
				launch_python = "python3 graph.py";
				launch_python += " 6";
				launch_python += " " + parsed_string[1] + "/radix_sort.csv";
				system(launch_python.c_str());
			}
			continue;
		}
		if(parsed_string[0] == "clear"){
			system("clear");
			continue;
		}
		if(parsed_string[0] == "exit"){
			cout << "Exiting..." << endl;
			break;
		}
	}
}

int main() {
	command_line();
}
