#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Directory {
    string name;
    int files_size;
    vector<Directory*> children;
    Directory* parent;

    int total_size;

    Directory(string name, Directory* parent) {
        this->name = name;
        files_size = 0;
        this->parent = parent;
    }

    void add_child(string name) {
        if (child_exists(name)) {
            return;
        }
        Directory* child = new Directory(name, this);
        children.push_back(child);
    }

    bool child_exists(string name) {
        for (Directory* child : children) {
            if (child->name == name) {
                return true;
            }
        }
        return false;
    }

    void add_file(int size) {
        files_size += size;
    }

    Directory* get_child(string name) {
        for (Directory* child : children) {
            if (child->name == name) {
                return child;
            }
        }
        return nullptr;
    }

    int set_total_size() {
        int total = files_size;
        for (Directory* child : children) {
            total += child->set_total_size();
        }
        total_size = total;
        return total;
    }

    void add_size(vector<int>& sizes) {
        if (total_size <= 100000) {
            sizes.push_back(total_size);
        }
        for (Directory* child : children) {
            child->add_size(sizes);
        }
    }
};



int main() {
    fstream data("../inputs/7.txt", ios::in);
    
    string line;

    Directory* root = new Directory("/", nullptr);
    Directory* current_dir = root;

    vector<int> sizes;

    while(getline(data, line)) {
        std::istringstream iss(line);
        string s;


        if (!(iss >> s)) { 
            break;
        }

        if (s == "$") {
            // command
            string command;
            iss >> command;

            if (command == "ls") {
                // do nothing
            } else { // cd
                string dir_path;
                iss >> dir_path;

                if (dir_path == "/") {
                    current_dir = root;
                } else if (dir_path == "..") {
                    current_dir = current_dir->parent;
                } else {
                    current_dir = current_dir->get_child(dir_path);
                }
            }
        } else {
            int size;
            string name;

            // check if item is numeral
            if (s[0] >= '0' && s[0] <= '9') {
                // file
                size = stoi(s);
                iss >> name;
                current_dir->add_file(size);
            } else {
                // directory
                iss >> name;
                current_dir->add_child(name);
            }
        }

    }

    root->set_total_size();
    // do stuff
    root->add_size(sizes);

    int sum = 0;
    for (int size : sizes) {
        sum += size;
    }
    cout << sum << endl;

    return 0;
}