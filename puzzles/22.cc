#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
/**
 * Note.  This only presently works for cube
 * data presented in the following format.
 * 
 * Rows > Columns
 * +------+
 * |  1122|
 * |  1122|
 * |  33  |
 * |  33  |
 * |4455  |
 * |4455  |
 * |66    |
 * |66    |
 * +------+ 
 */
class Grid {
    vector<vector<char>> grid;
    pair<int, int> start;
    pair<int, int> current;
    vector<pair<int, char>> commands;
    char orientation;
    int current_command = 0;
    int current_command_progress = 0;
    int N = 0;

    void parseCommands(const string &s);
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    void move_left_cube();
    void move_right_cube();
    void move_up_cube();
    void move_down_cube();
    void turn(char direction);

public:
    enum Show {
        GRID = 0,
        START_POSITION = 1,
        CURRENT_POSITION = 2,
        BOTH_POSITIONS = 3
    };
    void print(const Show &show = GRID);
    void printCommands();
    void init(const vector<string> &in, const string &s);
    void step();
    void step_cube();
    bool isDone() { return current_command >= commands.size(); }
    int command() { return current_command; }
    int password();
};
void Grid::step_cube() {
    if (current_command >= commands.size()) {
        return; // Reached the end
    }
    switch (orientation) {
    case '>':
        move_right_cube();
        break;
    case '<':
        move_left_cube();
        break;
    case 'v':
        move_down_cube();
        break;
    case '^':
        move_up_cube();
        break;
    default:
        break;
    }
    if (current_command_progress >= commands[current_command].first) {
        turn(commands[current_command].second);
        current_command++;
        current_command_progress = 0;
    }
}
void Grid::step() {
    if (current_command >= commands.size()) {
        return; // Reached the end
    }
    switch (orientation) {
    case '>':
        move_right();
        break;
    case '<':
        move_left();
        break;
    case 'v':
        move_down();
        break;
    case '^':
        move_up();
        break;
    default:
        break;
    }
    if (current_command_progress >= commands[current_command].first) {
        turn(commands[current_command].second);
        current_command++;
        current_command_progress = 0;
    }
}
int problem_a(Grid &grid) {
    while (!grid.isDone()) {
        grid.step();
        // grid.print(Grid::Show::CURRENT_POSITION);
    }
    return grid.password();
}

int problem_b(Grid &grid) {
    int last_command = -1;
    while (!grid.isDone()) {
        if (grid.command() != last_command) {
            // grid.print(Grid::Show::CURRENT_POSITION);
            int tmp=grid.command();
            last_command = tmp;
        }
        grid.step_cube();

    }
    return grid.password();
}

int main(int argc, char **argv) {

    string s;
    vector<string> g;
    bool more_grid = true;

    fstream data("../inputs/22.txt", ios::in);

    while (more_grid) {
        getline(data, s);
        if (s.size() > 0) {
            g.push_back(s);
        } else {
            getline(data, s);
            more_grid = false;
        }
    }

    Grid grida, gridb;
    grida.init(g, s);
    gridb.init(g, s);

    int ans1 = problem_a(grida);
    int ans2 = problem_b(gridb);

    cout << "Part 1: " << ans1 << "\n";
    cout << "Part 2: " << ans2 << "\n";
}

void Grid::init(const vector<string> &g, const string &commands) {
    parseCommands(commands);
    size_t R = g.size() + 2;
    size_t C = 0;
    for (auto r : g) {
        C = max(C, r.size());
    }
    N = C / 3;
    cout << "N=" << N << "   C=" << C << "   R=" << R - 2 << "   R/3" << (R - 2) / 3 << "\n";

    C = C + 2;
    grid.resize(R, vector<char>(C, ' '));
    bool looking_for_first = true;
    int row = 1;
    for (auto r : g) {
        int col = 1;
        for (auto c : r) {
            if (looking_for_first && c == '.') {
                start = {row, col};
                looking_for_first = false;
            }
            grid[row][col] = c;
            col++;
        }
        row++;
    }
    current = start;
    orientation = '>';
}
void Grid::print(const Show &show) {
    cout << "+";
    for (auto i = 0; i < grid[0].size(); i++) {
        cout << "-";
    }
    cout << "+\n";
    int row = 0;
    for (auto r : grid) {
        cout << "|";
        int col = 0;
        for (auto c : r) {
            if (show & START_POSITION && row == start.first &&
                col == start.second) {
                cout << "s";
            } else if (show & CURRENT_POSITION && row == current.first && col == current.second) {
                cout << orientation;
            } else {
                cout << c;
            }
            col++;
        }
        row++;
        cout << "|\n";
    }
    cout << "+";
    for (auto i = 0; i < grid[0].size(); i++) {
        cout << "-";
    }
    cout << "+\n";
}

void Grid::parseCommands(const string &s) {
    int start = 0;
    int end = 0;
    while (start < s.size()) {
        end = start + 1;
        while (s[end] >= '0' && s[end] <= '9') {
            end++;
        }
        int distance = stoi(s.substr(start, end - start));
        commands.push_back({distance, s[end]});
        start = end + 1;
    }
}

void Grid::printCommands() {
    for (auto [d, c] : commands) {
        cout << "Move " << d << " spaces then turn " << c << ".\n";
    }
}

void Grid::move_up() {
    current_command_progress++;
    int r = current.first - 1;
    if (r == 0) {
        r = grid.size() - 2;
    }
    while (grid[r][current.second] == ' ') {
        r--;
        if (r == 0) {
            r = grid.size() - 2;
        }
    }
    if (grid[r][current.second] == '#')
        return;

    current.first = r;
}
void Grid::move_down() {
    current_command_progress++;
    int r = current.first + 1;
    if (r == grid.size()) {
        r = 1;
    }
    while (grid[r][current.second] == ' ') {
        r++;
        if (r == grid.size()) {
            r = 1;
        }
    }
    if (grid[r][current.second] == '#')
        return;

    current.first = r;
}
void Grid::move_right() {
    current_command_progress++;
    int c = current.second + 1;
    if (c == grid[current.first].size()) {
        c = 1;
    }
    while (grid[current.first][c] == ' ') {
        c++;
        if (c == grid[current.first].size()) {
            c = 1;
        }
    }
    if (grid[current.first][c] == '#')
        return;

    current.second = c;
}
void Grid::move_left() {
    current_command_progress++;
    int r = current.first;
    int c = current.second - 1;
    if (c == 0) {
        c = grid[r].size() - 2;
    }
    while (grid[r][c] == ' ') {
        c--;
        if (c == 0) {
            c = grid[r].size() - 2;
        }
    }
    if (grid[r][c] == '#')
        return;

    current.second = c;
}

void Grid::turn(char direction) {
    if (direction == 'L' || direction == 'R') {
        switch (orientation) {
        case '>':
            if (direction == 'L')
                orientation = '^';
            else
                orientation = 'v';
            break;
        case '<':
            if (direction == 'L')
                orientation = 'v';
            else
                orientation = '^';

            break;
        case 'v':
            if (direction == 'L')
                orientation = '>';
            else
                orientation = '<';

            break;
        case '^':
            if (direction == 'L')
                orientation = '<';
            else
                orientation = '>';
            break;
        default:
            break;
        }
    }
}

int Grid::password() {
    int orientation_val = 0;
    if (orientation == '>')
        orientation_val = 0;
    if (orientation == 'v')
        orientation_val = 1;
    if (orientation == '<')
        orientation_val = 2;
    if (orientation == '^')
        orientation_val = 3;
    return current.first * 1000 + current.second * 4 + orientation_val;
}
/*
3->1 left faces right
2->1 top facing down
1->2 top facing down
6->4 right facing left
 */
void Grid::move_up_cube() {
    current_command_progress++;
    int r = current.first;
    int c = current.second;
    int nr = r - 1;
    int nc = c;
    int no = orientation;
    if (grid[nr][c] == '#') {
        return;
    }
    if (grid[nr][c] == ' ') {
        // wrapping
        if (c <= N) {
            nr = N + c;
            nc = N + 1;
            no = '>';
        } else if (c > N && c <= 2 * N) {
            nr = 3 * N + ((c - 1) % N) + 1;
            nc = 1;
            no = '>';
        } else { // c>2N
            nr = 4 * N;
            nc = ((c - 1) % N) + 1;
        }
        if (grid[nr][nc] == '#') {
            return;
        }
    }
    current.first = nr;
    current.second = nc;
    orientation = no;
}
void Grid::move_down_cube() {
    current_command_progress++;
    int r = current.first;
    int c = current.second;
    int nr = r + 1;
    int nc = c;
    int no = orientation;
    if (grid[nr][c] == '#') {
        return;
    }
    if (grid[nr][c] == ' ') {
        // wrapping
        if (c <= N) {
            nr = 1;
            nc = 2 * N + c;
        } else if (c > N && c <= 2 * N) {
            nr = 2 * N + c;
            nc = N;
            no = '<';
        } else { // c>2N
            nr = c - N;
            nc = 2 * N;
            no = '<';
        }
        if (grid[nr][nc] == '#') {
            return;
        }
    }
    current.first = nr;
    current.second = nc;
    orientation = no;
}
void Grid::move_right_cube() {
    current_command_progress++;
    int r = current.first;
    int c = current.second;
    int nr = r;
    int nc = c + 1;
    int no = orientation;
    if (grid[r][nc] == '#') {
        return;
    }
    if (grid[r][nc] == ' ') {
        // wrapping
        if (r > 3 * N) {
            nr = 3 * N;
            nc = r - 2 * N;
            no = '^';
        } else if (r > 2 * N) {
            nr = N - ((r - 1) % N);
            nc = 3 * N;
            no = '<';
        } else if (r > N) {
            nr = N;
            nc = r + N;
            no = '^';
        } else {
            nr = 3 * N - ((r - 1) % N);
            nc = 2 * N;
            no = '<';
        }
        if (grid[nr][nc] == '#') {
            return;
        }
    }
    current.first = nr;
    current.second = nc;
    orientation = no;
}
void Grid::move_left_cube() {
    current_command_progress++;
    int r = current.first;
    int c = current.second;
    int nr = r;
    int nc = c - 1;
    int no = orientation;
    if (grid[r][nc] == '#') {
        return;
    }
    if (grid[r][nc] == ' ') {
        // wrapping
        if (r > 3 * N) {
            nr = 1;
            nc = r - 2 * N;
            no = 'v';
        } else if (r > 2 * N) {
            nr = N - ((r - 1) % N);
            nc = N + 1;
            no = '>';
        } else if (r > N) {
            nr = 2 * N + 1;
            nc = r - N;
            no = 'v';
        } else {
            nr = 3 * N - ((r - 1) % N);
            nc = 1;
            no = '>';
        }
        if (grid[nr][nc] == '#') {
            return;
        }
    }
    current.first = nr;
    current.second = nc;
    orientation = no;
}