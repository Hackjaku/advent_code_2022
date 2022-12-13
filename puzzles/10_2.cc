#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    fstream data("../inputs/10.txt", ios::in);
    
    string line;

    int x_register = 1;
    int current_cycle = 0;

    cout << endl << endl;

    while(getline(data, line)) {
        std::istringstream iss(line);
        string c;
        int n;


        if (!(iss >> c)) { 
            break;
        }


        if (c == "noop") {

            if (current_cycle == 40) {
                current_cycle = 0;
                cout << endl;
            }            
            if (current_cycle <= x_register + 1 && current_cycle >= x_register - 1) {
                cout << "#";
            } else {
                cout << ".";
            }
            ++current_cycle;

        } else {
            iss >> n;
            if (current_cycle == 40) {
                current_cycle = 0;
                cout << endl;
            }   
            if (current_cycle <= x_register + 1 && current_cycle >= x_register - 1) {
                cout << "#";
            } else {
                cout << ".";
            }
            ++current_cycle;
            
            if (current_cycle == 40) {
                current_cycle = 0;
                cout << endl;
            }
            if (current_cycle <= x_register + 1 && current_cycle >= x_register - 1) {
                cout << "#";
            } else {
                cout << ".";
            }
            ++current_cycle;

            x_register += n;
        }

    }

    cout << endl << endl;

    return 0;
}