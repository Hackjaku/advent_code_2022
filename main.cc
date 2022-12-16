#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    fstream data("../inputs/10.txt", ios::in);
    
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