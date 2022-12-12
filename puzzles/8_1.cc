#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

bool is_visible(int, int, const int[99][99]);

int main() {
    fstream data("../inputs/8.txt", ios::in);
    
    string line;

    int tree_map[99][99] = { 0 };

    int i = 0;
    while(getline(data, line)) {
        std::istringstream iss(line);
        string s;

        if(!(iss >> s)) { 
            break;
        }

        for (int j = 0; j < s.length(); j++) {
            tree_map[i][j] = s[j] - '0';
        }
        ++i;
    }

    int visible_count = 0;
    for (int i = 0; i < 99; i++) {
        for (int j = 0; j < 99; j++) {
            if (is_visible(i, j, tree_map)) {
                ++visible_count;
            }
        }
    }

    cout << visible_count << endl;
    return 0;
}

bool is_visible(int row, int column, const int tree_map[99][99]) {
    if (row == 0 || column == 0 || row == 98 || column == 98) {
        return true;
    }

    int value = tree_map[row][column];

    top:
    for (int i = row - 1; i >= 0; --i) {
        if (tree_map[i][column] >= value) {
            goto bottom;
        }
    }
    return true;

    bottom:
    for (int i = row + 1; i < 99; ++i) {
        if (tree_map[i][column] >= value) {
            goto left;
        }
    }
    return true;

    left:
    for (int i = column - 1; i >= 0; --i) {
        if (tree_map[row][i] >= value) {
            goto right;
        }
    }
    return true;

    right:
    for (int i = column + 1; i < 99; ++i) {
        if (tree_map[row][i] >= value) {
            return false;
        }
    }
    return true;
}