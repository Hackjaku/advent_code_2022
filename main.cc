#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>

// #define HEIGHT 220
// #define WIDTH 380

// #define START_X 70
// #define START_Y 110

#define HEIGHT 100
#define WIDTH 100

#define START_X 50
#define START_Y 50

using namespace std;

void move_tail(int& tail_x, int& tail_y, int head_x, int head_y) {
    if (tail_x == head_x) {
        if (tail_y == head_y) {
            return;
        } else if (head_y == tail_y + 2) {
            tail_y++;
        } else if (head_y == tail_y - 2) {
            tail_y--;
        }
    } else if (tail_y == head_y) {
        if (head_x == tail_x + 2) {
            tail_x++;
        } else if (head_x == tail_x - 2) {
            tail_x--;
        }
    } else {
        if (head_x == tail_x + 2) {
            if (head_y == tail_y + 1) {
                tail_x++;
                tail_y++;
            } else if (head_y == tail_y - 1) {
                tail_x++;
                tail_y--;
            }
        } else if (head_x == tail_x - 2) {
            if (head_y == tail_y + 1) {
                tail_x--;
                tail_y++;
            } else if (head_y == tail_y - 1) {
                tail_x--;
                tail_y--;
            }
        } else if (head_y == tail_y + 2) {
            if (head_x == tail_x + 1) {
                tail_x++;
                tail_y++;
            } else if (head_x == tail_x - 1) {
                tail_x--;
                tail_y++;
            }
        } else if (head_y == tail_y - 2) {
            if (head_x == tail_x + 1) {
                tail_x++;
                tail_y--;
            } else if (head_x == tail_x - 1) {
                tail_x--;
                tail_y--;
            }
        }
    }
}

void print_grid(string grid[HEIGHT][WIDTH]) {
        // print grid
    std::cout << endl << endl;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            std::cout << grid[i][j];
        }
        std::cout << endl;
    }
}

void clear_grid(string grid[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = '.';
        }
    }
}

void execute(string grid[HEIGHT][WIDTH], int head_x, int head_y, int& tail_x, int& tail_y) {
    // populate grid with '+'
        move_tail(tail_x, tail_y, head_x, head_y);
        clear_grid(grid);
        grid[tail_x][tail_y] = "\033[1;36mT\033[0m";
        grid[head_x][head_y] = "\033[1;31mH\033[0m";
        system("clear");
        print_grid(grid);
        // std::this_thread::sleep_for(std::chrono::milliseconds(500));
        cin.get();
}

int main() {
    fstream data("../inputs/9.txt", ios::in);
    
    string line;

    int head_x = START_X;
    int head_y = START_Y;

    int tail_x = START_X;
    int tail_y = START_Y;

    string grid[HEIGHT][WIDTH];

    clear_grid(grid);

    grid[START_Y][START_X] = "\033[1;32mB\033[0m";

    std::cout << endl << endl;


    while(getline(data, line)) {
        std::istringstream iss(line);
        string d;
        int n;

        if (!(iss >> d >> n)) { 
            break;
        }

        if (d == "R") {
            for (int i = 0; i < n; i++) {
                ++head_y;
                execute(grid, head_x, head_y, tail_x, tail_y);
            }
        } else if (d == "L") {
            for (int i = 0; i < n; i++) {
                --head_y;
                execute(grid, head_x, head_y, tail_x, tail_y);
            }
        } else if (d == "U") {
            for (int i = 0; i < n; i++) {
                --head_x;
                execute(grid, head_x, head_y, tail_x, tail_y);
            }
        } else if (d == "D") {
            for (int i = 0; i < n; i++) {
                ++head_x;
                execute(grid, head_x, head_y, tail_x, tail_y);
            }
        }
        // do stuff
    }
    grid[START_Y][START_X] = "\033[1;32mB\033[0m";

    print_grid(grid);

    // int count = 0;
    // for (int i = 0; i < HEIGHT; i++) {
    //     for (int j = 0; j < WIDTH; j++) {
    //         if (grid[i][j] == "X") {
    //             count++;
    //         }
    //     }
    // }
    // std::cout << count << endl;

    return 0;
}