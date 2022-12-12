#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

bool is_control(int cycle, int control_cycles[]) {
    for (int i = 0; i < 6; i++) {
        if (cycle == control_cycles[i]) {
            return true;
        }
    }
    return false;
}

int main() {
    fstream data("../inputs/10.txt", ios::in);
    
    string line;

    int x_register = 1;
    int current_cycle = 1;

    int control_sum = 0;

    while(getline(data, line)) {
        std::istringstream iss(line);
        string c;
        int n;

        int control_cycles[] = { 20, 60, 100, 140, 180, 220 };

        if (!(iss >> c)) { 
            break;
        }

        if (c == "noop") {
            if (is_control(current_cycle, control_cycles)) {
                control_sum += x_register * current_cycle;
            }
            ++current_cycle;
            continue;
        } else {
            iss >> n;
            if (is_control(current_cycle, control_cycles)) {
                control_sum += x_register * current_cycle;
            }
            ++current_cycle;
            // control logic

            if (is_control(current_cycle, control_cycles)) {
                control_sum += x_register * current_cycle;
            }
            ++current_cycle;
            x_register += n;
        }

        // do stuff
    }

    std::cout << "Control sum: " << control_sum << endl;
    return 0;
}