#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int view_score(int, int, const int[99][99]);

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

    view_score(52, 14, tree_map);

    vector<int> scores;

    for (int i = 0; i < 99; i++) {
        for (int j = 0; j < 99; j++) {
            scores.push_back(view_score(i, j, tree_map));
        }
    }

    int max = 0;
    for (int i = 0; i < scores.size(); i++) {
        if (scores[i] > max) {
            max = scores[i];
        }
    }

    cout << max << endl;

    return 0;
}

int view_score(int row, int column, const int tree_map[99][99]) {
    int left_score = 0;
    int right_score = 0;
    int top_score = 0;
    int bottom_score = 0;

    int value = tree_map[row][column];

    top:
    if (row == 0) {
        return 0;
    }
    for (int i = row - 1; i >= 0; --i) {
        ++top_score;
        if (tree_map[i][column] >= value) {
            goto bottom;
        }
    }

    bottom:
    if (row == 98) {
        return 0;
    }
    for (int i = row + 1; i < 99; ++i) {
        ++bottom_score;
        if (tree_map[i][column] >= value) {
            goto left;
        }
    }

    left:
    if (column == 0) {
        return 0;
    }
    for (int i = column - 1; i >= 0; --i) {
        ++left_score;
        if (tree_map[row][i] >= value) {
            goto right;
        }
    }

    right:
    if (column == 98) {
        return 0;
    }
    for (int i = column + 1; i < 99; ++i) {
        ++right_score;
        if (tree_map[row][i] >= value) {
            break;
        }
    }

    return top_score * bottom_score * left_score * right_score;
}