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

    Directory(string name, Directory* parent) {
        this->name = name;
        files_size = 0;
        this->parent = parent;
    }

    void add_child(string name) {
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
};



int main() {
    fstream data("../inputs/7.txt", ios::in);
    
    string line;

    Directory* root = new Directory("/", nullptr);

    while(getline(data, line)) {
        std::istringstream iss(line);
        string s;

        if (!(iss >> s)) { 
            break;
        }

        if (s == "$") {
            // command
        } else {
            // directory
        }

        // do stuff
    }
    return 0;
}