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

        char header[14];

        for (int i = 13; i < s.length(); i++) {
            header[0] = s[i - 13];
            header[1] = s[i - 12];
            header[2] = s[i - 11];
            header[3] = s[i - 10];
            header[4] = s[i - 9];
            header[5] = s[i - 8];
            header[6] = s[i - 7];
            header[7] = s[i - 6];
            header[8] = s[i - 5];
            header[9] = s[i - 4];
            header[10] = s[i - 3];
            header[11] = s[i - 2];
            header[12] = s[i - 1];
            header[13] = s[i];

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