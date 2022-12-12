#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>

#define HEIGHT 220
#define WIDTH 380

#define START_X 70
#define START_Y 110

// #define HEIGHT 50
// #define WIDTH 150

// #define START_X 70
// #define START_Y 25

using namespace std;

void initiate_coords(int coords[10][2]) {
    for (int i = 0; i < 10; i++) {
        coords[i][0] = START_X;
        coords[i][1] = START_Y;
    }
}

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
    } else if (head_x == tail_x + 2 && head_y == tail_y + 2) {
        tail_x++;
        tail_y++;
    } else if (head_x == tail_x + 2 && head_y == tail_y - 2) {
        tail_x++;
        tail_y--;
    } else if (head_x == tail_x - 2 && head_y == tail_y + 2) {
        tail_x--;
        tail_y++;
    } else if (head_x == tail_x - 2 && head_y == tail_y - 2) {
        tail_x--;
        tail_y--;
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

void execute(string grid[HEIGHT][WIDTH], int rope_coords[10][2]) {
    // populate grid with '+'
        // clear_grid(grid);
        // grid[rope_coords[0][1]][rope_coords[0][0]] = "\033[1;33mH\033[0m";
        for (int i = 1; i < 10; i++) {
            move_tail(rope_coords[i][0], rope_coords[i][1], rope_coords[i-1][0], rope_coords[i-1][1]);
            // grid[rope_coords[i][1]][rope_coords[i][0]] = ("\033[1;36m" + to_string(i) + "\033[0m");
        }
        grid[rope_coords[9][1]][rope_coords[9][0]] = "\033[1;31mT\033[0m";
        // system("clear");
        // print_grid(grid);
        // std::this_thread::sleep_for(std::chrono::milliseconds(500));
        // cin.get();
}

int main() {
    fstream data("../inputs/9.txt", ios::in);
    
    string line;

    int rope_coords[10][2];
    initiate_coords(rope_coords);

    string grid[HEIGHT][WIDTH];

    clear_grid(grid);

    // grid[START_Y][START_X] = "\033[1;32mB\033[0m";
    // grid[START_Y][START_X] = "\033[1;36mH\033[0m";
    // print_grid(grid);

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
                ++rope_coords[0][0];
                execute(grid, rope_coords);
            }
        } else if (d == "L") {
            for (int i = 0; i < n; i++) {
                --rope_coords[0][0];
                execute(grid, rope_coords);
            }
        } else if (d == "U") {
            for (int i = 0; i < n; i++) {
                --rope_coords[0][1];
                execute(grid, rope_coords);
            }
        } else if (d == "D") {
            for (int i = 0; i < n; i++) {
                ++rope_coords[0][1];
                execute(grid, rope_coords);
            }
        }
    }

    // grid[START_Y][START_X] = "\033[1;32mB\033[0m";
    print_grid(grid);

    int count = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (grid[i][j] == "\033[1;31mT\033[0m") {
                count++;
            }
        }
    }
    std::cout << count << endl;

    return 0;
}