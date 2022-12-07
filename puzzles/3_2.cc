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

    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int i = 0;
    string r1, r2, r3;
    while(getline(data, line)) {
        std::istringstream iss(line);
        string s;
        if (!(iss >> s)) { 
            break;
        }
        if (i == 0) {
            r1 = s;
            ++i;
        } else if (i == 1) {
            r2 = s;
            ++i;
        } else if (i == 2) {
            r3 = s;
            // do stuff
            for (auto c : alphabet) {
                bool c1 = false, c2 = false, c3 = false;

                for (auto cs : r1) {
                    if (c == cs) {
                        c1 = true;
                        break;
                    }
                }
                if (!c1) {
                    continue;
                }

                for (auto cs : r2) {
                    if (c == cs) {
                        c2 = true;
                        break;
                    }
                }
                if (!c2) {
                    continue;
                }

                for (auto cs : r3) {
                    if (c == cs) {
                        c3 = true;
                        break;
                    }
                }
                if (!c3) {
                    continue;
                }
                total += calculate_priority(c);
                i = 0;
                break;
            }
        }
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