#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
    fstream data("../inputs/6.txt", ios::in);
    
    string line;

    while(getline(data, line)) {
        std::istringstream iss(line);
        string s;

        if (!(iss >> s)) { 
            break;
        }

        char header[4];

        for (int i = 3; i < s.length(); i++) {
            header[0] = s[i - 3];
            header[1] = s[i - 2];
            header[2] = s[i - 1];
            header[3] = s[i];

            std::sort(std::begin(header), std::end(header));
            auto pos = std::adjacent_find(std::begin(header), std::end(header));
            if (pos == std::end(header)) {
                cout << i + 1;
                break;
            }
        }
        cout << endl;

        // do stuff
    }
    return 0;
}