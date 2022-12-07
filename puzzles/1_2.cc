#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <vector>
#include <boost/range/algorithm.hpp>

using namespace std;
using namespace boost;

int main() {
    fstream data("../inputs/1_1.txt", ios::in);
    
    string line;

    vector<int> values;
    int current = 0;

    while(getline(data, line)) {
        std::istringstream iss(line);
        int a;
        if (!(iss >> a)) { 
            values.push_back(current);
            current = 0;
            continue;
        }
        current += a;
    }

    sort(values);

    int high_sum = 0;
    for (int i = 0; i < 3; i++) {
        high_sum += values[values.size() - i - 1];
    }

    cout << high_sum << endl;
    
    return 0;
}