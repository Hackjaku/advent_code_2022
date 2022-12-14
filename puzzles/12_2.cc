#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <vector>
#include <limits.h>
#include <stdio.h>
#include <algorithm>

#include "../models/PathFinder.h"

using namespace std;

#define MAZE_HEIGHT 41
#define MAZE_WIDTH 161

typedef vector<vector<char>> maze_t;

int main() {
    fstream data("../inputs/12.txt", ios::in);
    
    string line;

    maze_t maze;

    int row = 0;
    vector<char> row_vec;

    while(getline(data, line)) {
        std::istringstream iss(line);
        string s;

        row_vec.clear();

        if (!(iss >> s)) { 
            break;
        }

        for (int column = 0; column < MAZE_WIDTH; column++) {
            row_vec.push_back(s[column]);
        }
        maze.push_back(row_vec);

        ++row;
    }

    // INPUT DONE

    cout << "input done\n";

    auto pf = PathFinder(maze);

    pf.setDestination();

    vector<int> distances;
    for (int i = 0; i < MAZE_HEIGHT; ++i) {
        cout << i << endl;
        pf.setStart(i, 0);
        distances.push_back(pf.computeShortestPath());
    }

    std::sort(distances.begin(), distances.end());
    // print distances
    for (const auto &val : distances) {
        cout << val << endl;
    }
    
    return 0;
}
