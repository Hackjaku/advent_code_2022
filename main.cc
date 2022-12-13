#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#define MAZE_HEIGHT 41
#define MAZE_WIDTH 161

int main() {
    fstream data("../inputs/12.txt", ios::in);
    
    string line;

    char maze[MAZE_HEIGHT][MAZE_WIDTH];

    while(getline(data, line)) {
        std::istringstream iss(line);
        string s;

        if (!(iss >> s)) { 
            break;
        }

        // do stuff
    }
    return 0;
}