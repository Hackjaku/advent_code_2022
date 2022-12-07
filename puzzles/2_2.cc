#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

int main() {
    fstream data("../inputs/2_1.txt", ios::in);
    
    string line;

    int total = 0;

    int calculate_outcome(string, string);
    string calculate_figure(string, string);

    while(getline(data, line)) {
        std::istringstream iss(line);
        string result, opponent;
        if (!(iss >> opponent >> result)) {
            break;;
        }
        string me = calculate_figure(opponent, result);
        total += calculate_outcome(me, opponent);
    }
    
    cout << total << endl;

    return 0;
}

string calculate_figure(string opponent, string result) {
    if (opponent == "A") { // rock
        if (result == "X") { // must lose
            return "C"; // scissors
        } if (result == "Y") { // must draw
            return "A"; // rock
        } else { // must win
            return "B"; // paper
        }
    } else if (opponent == "B") { // paper
        if (result == "X") { // must lose
            return "A"; // rock
        } if (result == "Y") { // must draw
            return "B"; // paper
        } else { // must win
            return "C"; // scissors
        }
    } else { // scissors
        if (result == "X") { // must lose
            return "B"; // paper
        } if (result == "Y") { // must draw
            return "C"; // scissors
        } else { // must win
            return "A"; // rock
        }
    }
}

int calculate_outcome(string a, string b) {
    if (a == "A") { // rock
        if (b == "A") { // rock
            return 4; // draw (1 + 3)
        } else if (b == "B") { // paper
            return 1; // lose (1 + 0)
        } else {
            return 7; // win (1 + 6)
        }
    } else if (a == "B") { // paper
        if (b == "A") { // rock
            return 8; // win (2 + 6)
        } else if (b == "B") { // paper
            return 5; // draw (2 + 3)
        } else { // scissors
            return 2; // lose (2 + 0)
        }
    } else { // scissors
        if (b == "A") { // rock
            return 3; // lose (3 + 0)
        } else if (b == "B") { // paper
            return 9; // win (3 + 6)
        } else { // scissors
            return 6; // draw (3 + 3)
        }
    }
}
