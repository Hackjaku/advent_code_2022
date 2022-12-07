#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <boost/algorithm/string.hpp>

using namespace std;

void move(vector<char> stacks[], int from, int amount, int to) {
    vector<char> temp;
    for (int i = 0; i < amount; i++) {
        temp.push_back(stacks[from].back());
        stacks[from].pop_back();
    }
    for (int i = 0; i < amount; i++) {
        stacks[to].push_back(temp.back());
        temp.pop_back();
    }
}

int main() {
    fstream data("../inputs/5_processed.txt", ios::in);
    
    string line;

    vector<char> stacks[9];

    stacks[0] = { 'F', 'C', 'J', 'P', 'H', 'T', 'W'};
    stacks[1] = { 'G', 'R', 'V', 'F', 'Z', 'J', 'B', 'H' };
    stacks[2] = { 'H', 'P', 'T', 'R' };
    stacks[3] = { 'Z', 'S', 'N', 'P', 'H', 'T' };
    stacks[4] = { 'N', 'V', 'F', 'Z', 'H', 'J', 'C', 'D' };
    stacks[5] = { 'P', 'M', 'G', 'F', 'W', 'D', 'Z' };
    stacks[6] = { 'M', 'V', 'Z', 'W', 'S', 'J', 'D', 'P' };
    stacks[7] = { 'N', 'D', 'S' };
    stacks[8] = { 'D', 'Z', 'S', 'F', 'M' };


    while(getline(data, line)) {
        std::istringstream iss(line);
        int amount, from, to;

        if (!(iss >> amount >> from >> to)) { 
            break;
        }

        move(stacks, from - 1, amount, to - 1);
    }

    for (int i = 0; i < 9; i++) {
        cout << stacks[i].back();
    }
    cout << endl;
    return 0;
}