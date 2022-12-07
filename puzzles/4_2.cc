#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <boost/algorithm/string.hpp>

using namespace std;

int main() {
    fstream data("../inputs/4.txt", ios::in);
    
    string line;
    int total = 0;

    while(getline(data, line)) {
        std::istringstream iss(line);
        string s;

        if (!(iss >> s)) { 
            break;
        }

        vector<string> sectors;
        boost::split(sectors, s, boost::is_any_of(","));

        vector<string> sector_A;
        boost::split(sector_A, sectors[0], boost::is_any_of("-"));

        vector<string> sector_B;
        boost::split(sector_B, sectors[1], boost::is_any_of("-"));

        int a = stoi(sector_A[0]);
        int b = stoi(sector_A[1]);

        int c = stoi(sector_B[0]);
        int d = stoi(sector_B[1]);

        if ((c <= b && c >= a) || (a <= d && a >= c)) {
            total++;
        }
    }
    cout << total << endl;
    return 0;
}