#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <boost/algorithm/string.hpp>

using namespace std;

#define HEIGHT 164
#define WIDTH 700

#define SOURCE_X 500
#define SOURCE_Y 0

void add_sand(string maze[HEIGHT][WIDTH]);

int main() {
    fstream data("../inputs/14.txt", ios::in);
    
    string line;

    string maze[HEIGHT][WIDTH];
    // initialize maze with '.'
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            maze[i][j] = "\033[1;30m.\033[0m";
        }
    }

    maze[SOURCE_Y][SOURCE_X] = "\033[1;36m+\033[0m";

    while(getline(data, line)) {
        std::istringstream iss(line);
        string s;

        if (!(iss >> s)) { 
            break;
        }

        int x = -1;
        int y = -1;

        int prev_x = -1;
        int prev_y = -1;

        vector<string> tokens;
        boost::split(tokens, line, boost::is_any_of(" -> "), boost::token_compress_on);

        for (auto token : tokens) {
            vector<string> coords;
            boost::split(coords, token, boost::is_any_of(","));
            // print coords
            prev_x = x;
            prev_y = y;

            x = stoi(coords[0]);
            y = stoi(coords[1]);

            if (prev_x < 0) {
                continue;
            }

            if (prev_x != x) { // horizontal draw
                for (int i = min(prev_x, x); i <= max(prev_x, x); i++) {
                    maze[y][i] = "\033[1;31m#\033[0m";
                }
            } else {
                for (int i = min(prev_y, y); i <= max(prev_y, y); i++) {
                    maze[i][x] = "\033[1;31m#\033[0m";
                }
            }
        }
    }

    for (int i = 0; i < WIDTH; ++i) {
        maze[HEIGHT - 1][i] = "\033[1;31m#\033[0m";
    }

    int count = 0;

    while (true) {
        add_sand(maze);
        ++count;
        if (maze[SOURCE_Y][SOURCE_X] == "\033[1;32mo\033[0m") {
            break;
        }
    }
    cout << count << endl;

    // print maze
    // cout << endl << endl;
    // for (int i = 0; i < HEIGHT; i++) {
    //     for (int j = 0; j < WIDTH; j++) {
    //         cout << maze[i][j];
    //     }
    //     cout << endl;
    // }


    return 0;
}

void add_sand(string maze[HEIGHT][WIDTH]) {
    bool at_rest = false;
    int x = SOURCE_X, y = SOURCE_Y;
    while (!at_rest) {

        if (maze[y + 1][x] == "\033[1;30m.\033[0m") {
            ++y;
            continue;
        } else {
            if (maze[y + 1][x - 1] == "\033[1;30m.\033[0m") {
                --x;
                ++y;
                continue;
            } else if (maze[y + 1][x + 1] == "\033[1;30m.\033[0m") {
                ++x;
                ++y;
                continue;
            } else {
                maze[y][x] = "\033[1;32mo\033[0m";
                at_rest = true;
                return;
            }
        }
    }
}