#include <iostream>
#include <set>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <string>

using namespace std;
namespace fs = filesystem;

unordered_map<string, set<string>> read_map(string path) {
	unordered_map<string, set<string>> map;
	ifstream in_file;
	in_file.open(path);
	string line;
	while (getline(in_file, line)) {
		pair<string, set<string>> key_value;
		key_value.first = line.substr(0, line.find(":"));
		line = line.substr(line.find(":") + 1);
		while (true) {
			if ((signed)line.find("|") == -1) {
				key_value.second.insert(line);
				break;
			}
			else {
				key_value.second.insert(line.substr(0, line.find("|")));
				line = line.substr(line.find("|") + 1);
			}
		}
		map.insert(key_value);
	}
	return map;
}

void save_map(string root_path, unordered_map<string, set<string>>& map) {
	ofstream out_file;
	root_path = root_path.substr(root_path.find_last_of("/") + 1, root_path.length());
	out_file.open(root_path + ".map");
	unordered_map<string, set<string>>::iterator iterator = map.begin();
	while (iterator != map.end()) {
		auto pair_e = make_pair(iterator->first, iterator->second);
		out_file << pair_e.first << ":";
		set<string>::iterator pos;
		int counter = 0;
		for (pos = pair_e.second.begin(); pos != pair_e.second.end(); pos++) {
			if (counter != pair_e.second.size() - 1) {
				out_file << *pos << "|";
				counter++;
			}
			else {
				out_file << *pos << endl;
			}
		}
		iterator++;
	}
	out_file.close();
}

void print_map(unordered_map<string, set<string>>& map) {
	unordered_map<string, set<string>>::iterator iterator = map.begin();
	while (iterator != map.end()) {
		auto pair_e = make_pair(iterator->first, iterator->second);
		cout << "{" << pair_e.first << ": ";
		set<string>::iterator pos;
		int counter = 0;
		for (pos = pair_e.second.begin(); pos != pair_e.second.end(); pos++) {
			if (counter != pair_e.second.size() - 1) {
				cout << *pos << ",";
				counter++;
			}
			else {
				cout << *pos << "}" << endl;
			}
		}
		iterator++;
	}
}

string recursive_path_generator(string file_name, unordered_map<string, set<string>>& map, vector<string>& paths) {
	string full_path = "";
	if (map.find(file_name) == map.end()) {
		return "";
	}
	set<string> parents = map.find(file_name)->second;
	if (parents.size() == 1) {
		return recursive_path_generator(*parents.begin(), map, paths) + "/" + file_name;
	}
	else {
		for (auto parent : parents) {
			string c = parent;
			paths.push_back(recursive_path_generator(parent, map, paths) + "/" + file_name);
		}
	}
	return "1";
}

void generate_path(string file_name, string path, unordered_map<string, set<string>>& map) {
	vector<string> paths;
	string out = recursive_path_generator(file_name, map, paths);
	if (out == "") {
		cout << "'" << file_name << "' does not exist under " << path << endl;
	}
	else if (out != "1") {
		cout << path << out << endl;
	}
	for (int i = 0; i < paths.size(); i++) {
		cout << path << paths[i] << endl;
	}
}

set<string> get_parents(string file_name, unordered_map<string, set<string>>& map) {
	unordered_map<string, set<string>>::iterator iterator = map.find(file_name);
	if (iterator == map.end()) {
		cout << "No element present in map" << endl;
	}
	return iterator->second;
}

void navigate_curr_dir(string path_name, unordered_map<string, set<string>>& map) {
	for (auto& entry : fs::directory_iterator(path_name)) {
		string dir_file_name = entry.path().string();
		string parent = path_name.substr(path_name.find_last_of("/") + 1, path_name.length());
		dir_file_name = dir_file_name.substr(dir_file_name.find_last_of("/\\") + 1, dir_file_name.length());
		if (map.find(dir_file_name) == map.end()) {
			set<string> parents_list;
			parents_list.insert(parent);
			map.insert(make_pair(dir_file_name, parents_list));
		}
		else {
			map[dir_file_name].insert(parent);
		}
		if (fs::is_directory(path_name + "/" + dir_file_name)) {
			navigate_curr_dir(path_name + "/" + dir_file_name, map);
		}
	}
}

void command_line() {
	string input = "";
	while (true) {
		cout << ">> ";
		cin >> input;
		if (input == "help") {
			cout << "Exiting program...";
		}
	}
}

int main() {
	unordered_map<string, set<string>> file_system_index;
	string root_path = "D:/temporary/root"; //main pc
	//string root_path = "/home/kurt/github/FileSystemCrawler/root"; //linux machine
	//string root_path = "C:/Users/KURT/github/FileSystemCrawler/root"; //secondary pc
	//string root_path = "C:/Users/kurt_/github/FileSystemCrawler/root" //surface pro
	navigate_curr_dir(root_path, file_system_index);
	print_map(file_system_index);
	cout << endl;
	//save_map("C:/Users/KURT/Documents/Workspaces/visual_studio_workspace/FileSystemCrawler/FileSystemCrawler", file_system_index);
	//unordered_map<string, set<string>> map_read = read_map("root.map");
	//print_map(map_read);
	//auto t = get_parents("fil.dat", file_system_index);
	vector<string> paths;
	//generate_path("file.dat", root_path, file_system_index);
	generate_path("file.dat", root_path, file_system_index);
}
