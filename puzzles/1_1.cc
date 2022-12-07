#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    fstream data("../inputs/1_1.txt", ios::in);
    
    string line;

    int max = 0;
    int current = 0;

    while(getline(data, line)) {
        std::istringstream iss(line);
        int a;

        if (!(iss >> a)) { 
            if (current > max) {
                max = current;
            }
            current = 0;
            continue;
        }
        current += a;
    }
    cout << max << endl;
    return 0;
}