#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int calculate_distance(int x_a, int x_b, int y_a, int y_b) {
    return abs(x_a - x_b) + abs(y_a - y_b);
}

int calculate_covered_space(int x, int y, int nearest_beacon_distance, int perpendicular_distance) {
    int iteration = nearest_beacon_distance - perpendicular_distance;
    if (iteration < 0) {
        return 0;
    }
    int covered_space = 1;
    for (int i = 0; i < iteration; i++) {
        covered_space += 2;
    }
    return covered_space;
}

void row_coverage(int x, int y, int nearest_beacon_distance, int perpendicular_distance, int& from_x, int& to_x) {
    int covered_space = calculate_covered_space(x, y, nearest_beacon_distance, perpendicular_distance);
    from_x = x - covered_space / 2;
    to_x = x + covered_space / 2;
}

vector<int> distances;
vector<pair<int, int>> sensors;
vector<pair<int,int>> beacons;

int main() {
    fstream data("../inputs/15.txt", ios::in);
    
    string line;

    while(getline(data, line)) {
        int sensor_x, sensor_y, beacon_x, beacon_y;
        std::istringstream iss(line);
        if (!(iss >> sensor_x >> sensor_y >> beacon_x >> beacon_y)) { 
            break;
        }

        // do stuff
        distances.push_back(calculate_distance(sensor_x, beacon_x, sensor_y, beacon_y));
        pair<int, int> sensor = make_pair(sensor_x, sensor_y);
        sensors.push_back(sensor);

        pair<int, int> beacon = make_pair(beacon_x, beacon_y);
        // push if not already in the vector
        if (find(beacons.begin(), beacons.end(), beacon) == beacons.end()) {
            beacons.push_back(beacon);
        }
    }

    vector<pair<int, int>> coverages;

    for (int i = 0; i < sensors.size(); i++) {
        int x = sensors[i].first;
        int y = sensors[i].second;
        int distance = abs(y - 2000000);
        int from_x, to_x;
        row_coverage(x, y, distances[i], distance, from_x, to_x);
        pair<int, int> coverage = make_pair(from_x, to_x);
        // cout << "sensor: " << i << " covers from " << from_x << " to " << to_x << endl;
        coverages.push_back(coverage);
    }

    cout << "done" << endl;

    int min_x = coverages[0].first;
    int max_x = coverages[0].second;

    for (int i = 1; i < coverages.size(); i++) {
        if (coverages[i].first < min_x) {
            min_x = coverages[i].first;
        }
        if (coverages[i].second > max_x) {
            max_x = coverages[i].second;
        }
    }

    cout << "min_x: " << min_x << endl;
    cout << "max_x: " << max_x << endl;

    int covered_space = max_x - min_x;
    cout << "covered space: " << covered_space << endl;

    return 0;
}