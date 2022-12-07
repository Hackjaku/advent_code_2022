#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Directory {
    string name;
    int files_size;
    vector<Directory> children;
};

int main() {
    fstream data("../inputs/7.txt", ios::in);
    
    string line;

    while(getline(data, line)) {
        std::istringstream iss(line);
        string s;

        if (!(iss >> s)) { 
            break;
        }

        // do stuff
    }
    return 0;
}