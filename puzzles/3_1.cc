#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int calculate_priority(char);

int main() {
    fstream data("../inputs/3.txt", ios::in);
    
    string line;
    int total = 0;

    while(getline(data, line)) {
        std::istringstream iss(line);
        string s;
        if (!(iss >> s)) { 
            break;
        }
        for (int i = 0; i < s.length() / 2; ++i) {
            char c = s[i];
            for (int j = s.length() / 2; j < s.length(); ++j) {
                if (c == s[j]) {
                    total = total + calculate_priority(c);
                    goto next;
                }
            }
        }
        next:
        continue;
    }    
    cout << total << endl;
    return 0;
}

int calculate_priority(char c) {
    auto ascii_value = (int) c;
    if (ascii_value >= 65 && ascii_value <= 90) {
        return ascii_value - 38;
    } else if (ascii_value >= 97 && ascii_value <= 122) {
        return ascii_value - 96;
    } else {
        return 0;
    }
}