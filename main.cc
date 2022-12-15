#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <boost/algorithm/string.hpp>

using namespace std;

#define HEIGHT 200
#define WIDTH 550

int main() {
    fstream data("14.txt", ios::in);
    
    string line;

    char maze[HEIGHT][WIDTH];
    // initialize maze with '.'
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            maze[i][j] = '.';
        }
    }

    // // print maze
    // for (int i = 0; i < HEIGHT; i++) {
    //     for (int j = 0; j < WIDTH; j++) {
    //         cout << maze[i][j];
    //     }
    //     cout << endl;
    // }

    while(getline(data, line)) {
        std::istringstream iss(line);
        string s;

        if (!(iss >> s)) { 
            break;
        }

        vector<string> tokens;
        boost::split(tokens, line, boost::is_any_of(" -> "), boost::token_compress_on);

        for (auto token : tokens) {
            vector<string> coords;
            boost::split(coords, token, boost::is_any_of(","));
            // print coords
            for (auto coord : coords) {
                cout << coord << endl;
            }
        }
    }

    return 0;
}